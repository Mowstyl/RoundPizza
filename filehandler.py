 #!/usr/bin/python

import numpy as np
import heapq
import sys

# In this file we have the methods to parse the input file

def get_first(item_list):
    return heapq.heappop(item_list)

def insert_item(item_list, item):
    heapq.heappush(item_list, item)

def loadPFile(filepath):
	items = []
	n_lines = 1
	separator = " "
	f = open(filepath, "r")
	if f == None:
		raise ValueError("File not found!")
	first_line = f.readline().split(separator)
	if len(first_line) != 2:
		raise ValueError('Bad formatted file!')
	try:
		max_slices, types_pizza = [int(x) for x in first_line]
	except:
		raise ValueError('Must be integers!')
	if max_slices < 1 or max_slices > 10**9 or types_pizza < 1 or types_pizza > 10**5:
		raise ValueError('Limits error')
	for i in range(n_lines):
		line = f.readline()
		arr = list(map(int, line.split(separator)))
		#for e in arr:
			#insert_item(items, e)
	#for e in range(len(items)):
		#print(get_first(items))
	return max_slices, types_pizza, arr

#loadPFile(sys.argv[1])


def savePFile(filepath, n_types, list_types):
    f = open(filepath, "w+")
    f.write(str(n_types) + '\n')
    for i in range(len(list_types)-1):
        f.write(str(list_types[i]) + ' ')
    f.write(str(list_types[len(list_types)-1]))
    f.close()

#loadPFile(sys.argv[1])
#savePFile("output.out", 4, [1,2,3,4])


'''
def loadPFile(filename):
	f = open(filename, "r")
	if f == None:
		raise ValueError("File not found!")
	first = f.readline().split()
	if len(first) != 4:
		raise ValueError('Bad formatted file! First line must contain "R C L H"')
	try:
		r, c, l, h = [int(x) for x in first]
	except:
		raise ValueError('R, C, L and H must be integers!')
	if r < 1 or r > 1000 or c < 1 or c > 1000 or l < 1 or l > 1000 or h < 1 or h > 1000:
		raise ValueError('R, C, L, H must be between 1 and 1000 included!')
	if 2*l > h:
		raise ValueError("Maximum number of cells per slice can't be smaller than 2 x number of cells of each type")
	pizza = []
	countT = 0
	countM = 0
	for i in range(r):
		line = f.readline()
		if line == None:
			raise ValueError("Invalid number of rows! Expected " + str(r))
		line = line.strip()
		if len(line) != c:
			raise ValueError("Invalid number of columns! Expected " + str(c) + " Found " + str(len(line)))
		row = []
		for char in line:
			if char == "M":
				row.append(0)
				countM += 1
			elif char == "T":
				row.append(1)
				countT += 1
			else:
				raise ValueError("Invalid character! Please only use M and T!")
		pizza.append(row)
	return (r, c, l, h, np.array(pizza), countM, countT)

# In this file we have the methods to parse the input file
def savePFile(filename, sol):
	f = open(filename, "w+")
	f.write(str(sol[0]) + '\n')
	for split in sol[1]:
		f.write(str(split[0][0]) + ' ' + str(split[0][1]) + ' ' + str(split[1][0]) + ' ' + str(split[1][1]) + '\n')
		'''
