 #!/usr/bin/python
import json
import numpy as np
import heapq
import sys

# In this file we have the methods to parse the input file
class Data_manager:
	
	heap = []
	filepath = None
	heuristic = None
	
	def __init__(self, filepath="data.txt", heuristic=lambda x: 0):
		self.filepath = filepath
		self.heuristic = heuristic
	
	def get_first(self):
		return heapq.heappop(self.heap)[1]

	def insert_item(self, item):
		heapq.heappush(self.heap, (self.heuristic(item), item))

	def loadPFile(self, filepath):
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



	def savePFile(self, filepath, n_types, list_types):
		f = open(filepath, "w+")
		f.write(str(n_types) + '\n')
		for i in range(len(list_types)-1):
			f.write(str(list_types[i]) + ' ')
		f.write(str(list_types[len(list_types)-1]))
		f.close()

	def to_json(self, filepath, data):
		with open(filepath, 'w') as file:
			json.dump(data, file)
			
	def to_memory(self, filepath):
		with open(filepath) as file:
			data = json.load(file)
		return data

	def test(self):
		heap=[]
		items = [(14,"jasd"),(33,"qwe"),(15,"cxdv"),(2,"asx"),(7,"2221q"),(1,"ry5"),(4,"bcx")]
		self.to_json("data.json", items)
		data = self.to_memory("data.json")
		print(data)
		for i in items:
			self.insert_item(i[1])
		print("insertados")
		for i in range(len(self.heap)):
			print(self.get_first())
		print("impresos")
		
#a = Data_manager(heuristic=lambda x: len(x))
#a.test()