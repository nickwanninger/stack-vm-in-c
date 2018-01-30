import struct

types = {
	"byte": "b",
	"ubyte": "B",
	"short": "h",
	"ushort": "H",
	"int": "i",
	"uint": "I",
	"float": "f",
	"double": "d"
}

class Bytewriter:
	def __init__(self, file):
		self.file = file
		self.bytes_written = 0
	def write(self, val, t):
		packed = struct.pack(types[t], val)
		b = bytes(packed)
		self.bytes_written += len(b)
		self.file.write(b)