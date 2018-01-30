import re
import ctypes
import math
from optparse import OptionParser
from Bytewriter import Bytewriter

class Label:
	def __init__(self, name):
		self.name = name
		self.raw_lines = []
	def push_line(self, line):
		# print(self.name)
		tokens = line.split()
		# print(tokens)

parser = OptionParser()
(options, args) = parser.parse_args()

source_file = open(args[0], "r")
# Read the file as a string
source_text = source_file.read()
# Remove comments
source_text = re.sub("(;.+\n?)", "\n",  source_text)
# Split the text into a list of lines
lines = source_text.split("\n")


label_re = re.compile("label (\w+):")
labels = {}
current_label = ""

labels["_global_"] = Label("_global_")

for l in lines:
	tokens = l.split()
	if len(tokens) > 0:
		if tokens[0] == "end":
			current_label = "_global_"

		label_match = label_re.match(l)
		if label_match:
			name = label_match.groups()[0]
			current_label = name
			labels[current_label] = Label(current_label)
		else:
			labels[current_label].push_line(l)
		print(current_label, tokens)


# exit()

outputfile = open('a.out', 'wb')
bytes_written = 0



writer = Bytewriter(outputfile)

# PUSH 1
writer.write(3, "byte")
writer.write(1, "short")
# PUSH 1
writer.write(3, "byte")
writer.write(1, "short")
# ADD
writer.write(4, "byte")
# # EMIT
writer.write(2, "byte")
# HALT
writer.write(1, "byte")

outputfile.close()