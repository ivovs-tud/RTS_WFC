"""Optional application-level UDP/solver timing; disk writes stay off hot paths."""

import csv
from contextlib import ExitStack
import json
from pathlib import Path
import queue
import struct
import sys
import tempfile
import threading
import time
from typing import NamedTuple


TIMING_TRAILER = struct.Struct("<IQ")
PACKET_COLUMNS = (
    "run_id", "stream", "event", "seq", "pc_unix_ns", "pc_monotonic_ns",
    "sender_unix_ns", "payload_bytes",
)
STEP_COLUMNS = (
    "run_id", "step", "step_start_unix_ns", "step_start_mono_ns",
    "input_snapshot_mono_ns", "step_end_mono_ns", "used_rts_seq",
    "used_rts_rx_mono_ns", "used_rts_rx_unix_ns",
)


class ReceiveMetadata(NamedTuple):
    seq: int | None
    sender_unix_ns: int | None
    pc_unix_ns: int
    pc_monotonic_ns: int


def split_timing_trailer(packet: bytes) -> tuple[bytes, int, int]:
    """Separate the unmodified signal bytes and the little-endian trailer."""
    if len(packet) < TIMING_TRAILER.size:
        raise ValueError("UDP packet is shorter than the timing trailer")
    payload_end = len(packet) - TIMING_TRAILER.size
    seq, sender_unix_ns = TIMING_TRAILER.unpack_from(packet, payload_end)
    return packet[:payload_end], seq, sender_unix_ns


class TimingLog:
    """Bounded, nonblocking producers with one buffered CSV writer thread.

    Stop communication/simulation producers before close(). Accepted records are
    drained at close; overflow and disk failures are reported in the run status.
    """

    def __init__(self, root: Path, queue_size: int = 65536):
        if queue_size <= 0:
            raise ValueError("queue_size must be positive")
        root = Path(root).expanduser().resolve()
        root.mkdir(parents=True, exist_ok=True)
        self.run_dir = Path(tempfile.mkdtemp(prefix=f"run_{time.time_ns()}_", dir=root))
        self.run_id = self.run_dir.name
        self._queue = queue.Queue(maxsize=queue_size)
        self._closing = threading.Event()
        self._closed = False
        self._writer_error = None
        self.dropped_records = {"packet": 0, "step": 0}
        self._drop_lock = threading.Lock()
        self._files = ExitStack()
        try:
            self._streams = [
                self._files.enter_context((self.run_dir / name).open("x", newline=""))
                for name in ("pc_packet_events.csv", "pc_ff_steps.csv")
            ]
            self._writers = [csv.writer(stream) for stream in self._streams]
            for writer, columns in zip(self._writers, (PACKET_COLUMNS, STEP_COLUMNS)):
                writer.writerow(columns)
            self._thread = threading.Thread(
                target=self._write_loop, name="TimingCSVWriter", daemon=True
            )
            self._thread.start()
        except Exception:
            self._files.close()
            raise

    def _enqueue(self, kind: int, row: tuple) -> None:
        if not self._closing.is_set() and self._writer_error is None:
            try:
                self._queue.put_nowait((kind, row))
                return
            except queue.Full:
                pass
        with self._drop_lock:
            self.dropped_records[("packet", "step")[kind]] += 1

    def packet(self, stream, event, seq, unix_ns, mono_ns, sender_unix_ns, packet_bytes):
        self._enqueue(0, (
            self.run_id, stream, event, seq, unix_ns, mono_ns,
            sender_unix_ns, packet_bytes,
        ))

    def step(self, step, start_unix_ns, start_mono_ns, snapshot_mono_ns,
             end_mono_ns, used_packet: ReceiveMetadata | None):
        self._enqueue(1, (
            self.run_id, step, start_unix_ns, start_mono_ns, snapshot_mono_ns,
            end_mono_ns, used_packet.seq if used_packet else None,
            used_packet.pc_monotonic_ns if used_packet else None,
            used_packet.pc_unix_ns if used_packet else None,
        ))

    def _write_loop(self):
        last_flush = time.monotonic()
        try:
            while not self._closing.is_set() or not self._queue.empty():
                try:
                    kind, row = self._queue.get(timeout=0.25)
                except queue.Empty:
                    pass
                else:
                    self._writers[kind].writerow(row)
                if time.monotonic() - last_flush >= 1.0:
                    for stream in self._streams:
                        stream.flush()
                    last_flush = time.monotonic()
        except Exception as exc:
            self._writer_error = repr(exc)
        finally:
            try:
                self._files.close()  # flush buffered rows, including on shutdown
            except Exception as exc:
                self._writer_error = repr(exc)

    def close(self):
        if self._closed:
            return
        self._closing.set()
        self._thread.join()
        self._closed = True
        status = {
            "run_id": self.run_id,
            "dropped_records": self.dropped_records,
            "writer_error": self._writer_error,
            "queued_records_unwritten": self._queue.qsize(),
        }
        try:
            with (self.run_dir / "pc_timing_status.json").open("x") as stream:
                json.dump(status, stream, indent=2)
        except OSError as exc:
            print(f"[TimingLog] Cannot save shutdown status: {exc}", file=sys.stderr)
        if self._writer_error or any(self.dropped_records.values()):
            print(f"[TimingLog] Incomplete timing logs: {status}", file=sys.stderr)

    def __enter__(self):
        return self

    def __exit__(self, *_):
        self.close()
