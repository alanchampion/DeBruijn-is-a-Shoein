import random
import sys

file = open("eulerian.in", "w+")

num_data = 101
if(len(sys.argv) > 1):
	num_data = int(sys.argv[1])

for x in range(num_data):
	file.write(str(random.randint(1,101)) + " " + str(random.randint(1,101)) + "\n")

file.close()