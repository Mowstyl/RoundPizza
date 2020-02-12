#!/usr/bin/python

import sys
import filehandler as fh
import math as m
import numpy as np
import ctypes as ct
import os
from os.path import dirname, abspath, sep
from math import sqrt
from itertools import count, islice
from timeit import default_timer as timer

__rootfolder__ = dirname(abspath(__file__))
__libfolder__ = __rootfolder__ + sep + "lib"
os.add_dll_directory(os.getcwd())
os.add_dll_directory(__libfolder__)

c_int_p = ct.POINTER(ct.c_int)

__pizzac__ = ct.CDLL("pizza.dll")
__pizzaSolver__ = __pizzac__.pizzaSolver
__pizzaSolver__.argtypes = [ct.c_int, ct.c_int, c_int_p, c_int_p, c_int_p]
__pizzaSolver__.restype = ct.c_int


def pedirPizza(maxSlices, nTypes, typeValues):
    int_array = ct.c_int * nTypes
    tval = int_array(*typeValues)
    solution = int_array(*[0 for i in range(nTypes)])
    score = c_int_p(ct.c_int(0))
    solnt = int(__pizzaSolver__(ct.c_int(maxSlices), ct.c_int(nTypes), tval, solution, score))

    return solnt, solution[:solnt], score.contents.value

def main(argv): # We expect to receive input file as first argument and output file second argument (optional). If output not specified, defaults to input+.out
	if len(argv) < 1:
		print("Input file location expected. Output file can be also specified (optional)")
		return
	input = argv[0]
	output = input + ".out"
	maxLevel = 5
	maxSlices = 50
	if len(argv) > 1:
		output = argv[1]
	try:
		maxs, nty, values = fh.loadPFile(input)
	except Exception as e:
		print (str(e))
		print ("Parse ended with errors!")
		return
	start = timer()
	usedty, listty, score = pedirPizza(maxs, nty, values)
	end = timer()
	print("\nTime elapsed: %.4f seconds." % round(end-start, 4))
	print ("Score: " + str(score) + "/" + str(maxs))
	fh.savePFile(output, usedty, listty)

if __name__ == "__main__":
	main(sys.argv[1:])
