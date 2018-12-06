import random
import sys

file = open("eulerian.in", "w+")

num_data = 101
if(len(sys.argv) > 1):
	num_data = int(sys.argv[1])

file.write("5000 " + str(num_data) + "\n")

for x in range(num_data):
	file.write(str(random.randint(1,5001)) + " " + str(random.randint(1,5001)) + "\n")

file.close()