
import struct
import zmq
import select
import sys
import time


class RequestedPowerTransmitter:

	# Packet that is sent continuously every INTERVAL_SECONDS.
	# Packed as raw float bytes (little-endian).
	SEND_PACKET = struct.pack('<f', 100.0)
	# SEND_PACKET = [int32(-1)]
	# ENTER_PACKET = [int32(0x01010101), int32(1)]

	# Packet sent only when Enter is pressed.
	# Raw bytes: 0x01010101 (4 bytes, big-endian) followed by float 1.0 (4 bytes).
	ENTER_PACKET = struct.pack('>IB', 0x01010101, 0)

	INTEGRITY_TIME = 60.0		# In milliseconds

	def __init__(self, server_ip: str, server_port: str):
		self.server_ip = server_ip
		self.server_port = server_port

		self.ctx  = zmq.Context()
		self.sock = self.ctx.socket(zmq.PAIR)
		# Don't buffer more than 1 message
		self.sock.setsockopt(zmq.SNDHWM, 3)
		self.last_transmitted = None
		self.last_transmitted_t = None

	def connect(self):
		self.sock.connect(f"tcp://{self.server_ip}:{self.server_port}")

	def tx_requested_power(self, t: float, w_spt: float):
		# If the w_spt is significantly different from last transmitted, or enough time has elapsed, we send
		if (self.last_transmitted is None or abs(self.last_transmitted - w_spt) > 0.1 or t - self.last_transmitted_t > self.INTEGRITY_TIME):
			send_pkt = self.pack_requested_power(w_spt)
			self.sock.send(send_pkt)
			print(f"Transmitted Power Reference: {w_spt} at time {t}")
			self.last_transmitted = w_spt
			self.last_transmitted_t = t
	
	def pack_requested_power(self, value: float) -> bytes:
		# Match the receiver's little-endian float layout.
		return struct.pack('<f', float(value))