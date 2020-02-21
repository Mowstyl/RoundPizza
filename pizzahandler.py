#!/usr/bin/python

import sys
import filehandler as fh
import math as m
import numpy as np
import ctypes as ct
import os
import random as rnd
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
#__pizzaSolver__.argtypes = [ct.c_int, ct.c_int, c_int_p, ct.c_int, c_int_p, c_int_p, c_int_p, c_int_p, ct.POINTER(c_int_p), c_int_p, c_int_p, ct.POINTER(c_int_p), c_int_p]
__pizzaSolver__.argtypes = [ct.c_int, ct.c_int, c_int_p, ct.c_int, c_int_p, c_int_p, c_int_p, c_int_p, c_int_p, c_int_p, c_int_p, c_int_p, c_int_p]
__pizzaSolver__.restype = ct.c_int

__pizzaRandom__ = __pizzac__.pizzaRandom
__pizzaRandom__.argtypes = [ct.c_int, ct.c_int, c_int_p, c_int_p, c_int_p, ct.c_int, ct.c_uint]
__pizzaRandom__.restype = ct.c_int


def pedirLibros(nlib, nbib, maxd, scores, librerias, ofile):
    array_libs = ct.c_int * nlib
    array_bibs = ct.c_int * nbib
    array_bibs_libs = ct.c_int * (nlib * nbib)
    nullptr = c_int_p(ct.c_int(0))
    libbib = array_bibs_libs(*[ct.c_int(b) for bib in librerias for b in bib.books])
    idbibs = array_bibs(*[ct.c_int(0) for i in range(nbib)])
    nbookbib = array_bibs(*[ct.c_int(0) for i in range(nbib)])
    idbooksbib = array_bibs_libs(*[ct.c_int(0) for i in range(nlib * nbib)])
    signupnum = c_int_p(ct.c_int(0))

    #print(librerias[0].books)

    #for i in range(nbib):
    #    for j in range(librerias[i].n_books):
    #        libbib[i][j] = librerias[i].books[j]

    #print([[libbib[i][j] for j in range(nlib)] for i in range(nbib)])

    #__pizzaSolver__.argtypes = [ct.c_int, ct.c_int, c_int_p, ct.c_int, c_int_p, c_int_p, c_int_p, c_int_p, array_bibs_libs, c_int_p, c_int_p, array_bibs_libs, c_int_p]
    #print ("Miauadada")
    score = int(__pizzaSolver__(ct.c_int(nlib), ct.c_int(maxd), array_libs(*scores), ct.c_int(nbib), array_bibs(*[ct.c_int(bib.n_books) for bib in librerias]), nullptr, array_bibs(*[ct.c_int(bib.signup_process) for bib in librerias]), array_bibs(*[ct.c_int(bib.ship) for bib in librerias]), libbib, idbibs, nbookbib, idbooksbib, signupnum))

    #print ("Miauaaa")
    signupnumC = int(signupnum.contents.value)
    #print ("Miaubbadab1 " + str(signupnumC))
    idbibsC = idbibs[:signupnumC]
    #print ("Miaubbadab2 " + str(idbibsC))
    nbookbibC = nbookbib[:signupnumC]
    #print ("Miaubbadab3 " + str(nbookbibC))
    idbooksbibC = [[idbooksbib[i*signupnumC+j] for j in range(nbookbibC[i])] for i in range(signupnumC)]
    #print ("Miaubbb")

    #print(score)
    #print(signupnumC)
    #print(idbibsC)
    #print(nbookbibC)
    #print(idbooksbibC)
    fh.savePFile(ofile, signupnumC, idbibsC, nbookbibC, idbooksbibC)
    print("Done!")

    return score, signupnumC, idbibsC, nbookbibC, idbooksbibC

def pedirPizzaRandom(maxSlices, nTypes, typeValues, niters, seed):
    int_array = ct.c_int * nTypes
    tval = int_array(*typeValues)
    solution = int_array(*[0 for i in range(nTypes)])
    score = c_int_p(ct.c_int(0))
    solnt = int(__pizzaRandom__(ct.c_int(maxSlices), ct.c_int(nTypes), tval, solution, score, ct.c_int(niters), ct.c_uint(seed)))

    return solnt, solution[:solnt], score.contents.value

def main(argv): # We expect to receive input file as first argument and output file second argument (optional). If output not specified, defaults to input+.out
    if len(argv) < 1:
        print("Input file location expected. Output file can be also specified (optional)")
        return
    input = argv[0]
    output = input + ".out"
    if len(argv) > 1:
        output = argv[1]

    niters = 20;
    seed = rnd.randint(0, 4294967295)
    if len(argv) > 2:
        niters = int(argv[2])
    if len(argv) > 3:
        seed = int(argv[3])

    try:
        nlib, nbib, maxd, scores, librerias = fh.loadPFile(input)
    except Exception as e:
        print (str(e))
        print ("Parse ended with errors!")
        return
    print ("Starting!")
    start = timer()
    score, num_librerias, lista_librerias, num_libros_por_libreria, lista_libros_librerias = pedirLibros(nlib, nbib, maxd, scores, librerias, output)
    #print ("miau")
    #usedtyr, listtyr, scorer = pedirPizzaRandom(maxs, nty, values, niters, seed)
    # print ("miau")
    #if scorer > score:
    #    usedty = usedtyr
    #    listty = listtyr
    #    score = scorer
    end = timer()
    print("\nTime elapsed: %.4f seconds." % round(end-start, 4))
    #print ("Score: " + str(score) + "/" + str(maxs))
    #fh.savePFile(output, num_librerias, lista_librerias, num_libros_por_libreria, lista_libros_librerias)

if __name__ == "__main__":
    main(sys.argv[1:])
