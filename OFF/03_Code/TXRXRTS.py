"""
Thread-safe UDP communication module.

Topology (two peers, A and B):
    Peer A  TX_PORT_A  -->  RX_PORT_B  Peer B
    Peer A  RX_PORT_A  <--  TX_PORT_B  Peer B

Each UDPComms instance owns:
  - one sender thread   : picks up the latest value set by the main thread and
                          transmits it at a fixed rate.
  - one receiver thread : continuously reads incoming datagrams and stores the
                          most recent one for the main thread to collect.

Thread-safety guarantees
  - threading.Lock  protects the shared send-value slot.
  - threading.Lock  protects the shared receive-value slot.
  - Neither lock is held while doing I/O, so the main thread is never blocked
    for more than the time of a single dict/bytes copy.
"""

import json
import socket
import threading
import time
from typing import Any
import numpy as np


class UDPComms:
    """
    Bidirectional, thread-safe UDP communicator.

    Parameters
    ----------
    local_ip        : IP to bind the receive socket to ('' = all interfaces).
    remote_ip       : IP of the remote peer to send to.
    tx_port         : UDP port this instance *sends* from (bound locally).
    rx_port         : UDP port this instance *receives* on (bound locally).
    send_interval   : seconds between send attempts (default 0.02 → 50 Hz).
    socket_timeout  : receive-socket timeout in seconds (default 1.0).
    encoding        : 'json' (default) or 'raw' (bytes pass-through).
    """

    def __init__(
        self,
        local_ip: str = "",
        remote_ip: str = "127.0.0.1",
        tx_port: int = 5005,
        rx_port: int = 5006,
        send_interval: float = 0.02,
        socket_timeout: float = 1.0,
        encoding: str = "json",
    ) -> None:
        if encoding not in ("json", "raw"):
            raise ValueError("encoding must be 'json' or 'raw'")

        self._remote_ip = remote_ip
        self._tx_port = tx_port
        self._rx_port = rx_port
        self._send_interval = send_interval
        self._encoding = encoding

        # ── shared state ──────────────────────────────────────────────────────
        self._send_value: Any = None          # latest value queued by main thread
        self._send_lock = threading.Lock()

        self._recv_value: Any = None          # latest value received from remote
        self._recv_lock = threading.Lock()

        self._stop_event = threading.Event()

        # ── sockets ───────────────────────────────────────────────────────────
        # TX socket: ephemeral source port; we send *to* remote_ip:tx_port
        self._tx_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # RX socket: bind to rx_port to receive datagrams sent to us
        self._rx_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._rx_sock.settimeout(socket_timeout)
        self._rx_sock.bind((local_ip, rx_port))

        # ── threads ───────────────────────────────────────────────────────────
        self._send_thread = threading.Thread(
            target=self._send_loop, name="UDPSender", daemon=True
        )
        self._recv_thread = threading.Thread(
            target=self._recv_loop, name="UDPReceiver", daemon=True
        )

    # ── public API ────────────────────────────────────────────────────────────

    def start(self) -> None:
        """Start the sender and receiver background threads."""
        self._stop_event.clear()
        self._send_thread.start()
        self._recv_thread.start()

    def stop(self) -> None:
        """Signal both threads to stop and wait for them to finish."""
        self._stop_event.set()
        self._send_thread.join()
        self._recv_thread.join()
        self._tx_sock.close()
        self._rx_sock.close()

    def set_send_value(self, value: Any) -> None:
        """
        Thread-safe. Stores *value* so the sender thread will transmit it next.
        Only the most recent value is ever sent; intermediate values are dropped.
        """
        with self._send_lock:
            self._send_value = value

    def get_recv_value(self) -> Any:
        """
        Thread-safe. Returns the most recently received value, or None if
        nothing has arrived yet.
        """
        with self._recv_lock:
            return self._recv_value

    # ── context-manager support ───────────────────────────────────────────────

    def __enter__(self) -> "UDPComms":
        self.start()
        return self

    def __exit__(self, *_) -> None:
        self.stop()

    # ── internal loops ────────────────────────────────────────────────────────

    def _send_loop(self) -> None:
        while not self._stop_event.is_set():
            loop_start = time.monotonic()

            with self._send_lock:
                value = self._send_value

            if value is not None:
                try:
                    payload = self._encode(value)

                    self._tx_sock.sendto(payload, (self._remote_ip, self._tx_port))
                except OSError as exc:
                    print(f"[UDPSender] send error: {exc}")

            elapsed = time.monotonic() - loop_start
            sleep_for = self._send_interval - elapsed
            if sleep_for > 0:
                time.sleep(sleep_for)

    def _recv_loop(self) -> None:
        while not self._stop_event.is_set():
            #print("Try to Receive")
            try:
                data, _ = self._rx_sock.recvfrom(2*9*4)
                value = self._decode(data)
                with self._recv_lock:
                    self._recv_value = value
            except socket.timeout:
                pass  # normal; lets us check _stop_event regularly
            except OSError as exc:
                if not self._stop_event.is_set():
                    print(f"[UDPReceiver] recv error: {exc}")

    # ── codec helpers ─────────────────────────────────────────────────────────

    def _encode(self, value: Any) -> bytes:
        #if self._encoding == "json":
        #    return json.dumps(value).encode()
        return value.T.flatten().view(np.uint8).tobytes()
        #return value  # raw: caller must provide bytes

    def _decode(self, data: bytes) -> Any:
        return np.frombuffer(data, dtype=np.float32)  # raw: return bytes as-is


# ── demo ──────────────────────────────────────────────────────────────────────

if __name__ == "__main__":
    """
    Self-contained loopback demo:  two UDPComms instances on localhost.

        node_a  sends on 5005  →  node_b receives on 5005
        node_b  sends on 5006  →  node_a receives on 5006
    """

    node_a = UDPComms(
        remote_ip="127.0.0.1", tx_port=5005, rx_port=5006, send_interval=0.1
    )
    node_b = UDPComms(
        remote_ip="127.0.0.1", tx_port=5006, rx_port=5005, send_interval=0.1
    )

    with node_a, node_b:
        for i in range(10):
            # Main thread writes the latest value for each node to send
            node_a.set_send_value(np.array([0.1, 0.3, 0.4], dtype=np.float32))
            node_b.set_send_value(np.array([0.2, 0.4, 0.5], dtype=np.float32))

            time.sleep(0.25)

            # Main thread reads the most recent value each node has received
            a_got = node_a.get_recv_value()
            b_got = node_b.get_recv_value()
            print(f"[step {i:02d}]  A received: {a_got}   |   B received: {b_got}")

    print("Done.")