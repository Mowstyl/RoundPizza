#!/usr/bin/python

import traceback
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
from estructuras import Biblioteca, Problema

__rootfolder__ = dirname(abspath(__file__))
__libfolder__ = __rootfolder__ + sep + "lib"
os.add_dll_directory(os.getcwd())
os.add_dll_directory(__libfolder__)

c_uint_p = ct.POINTER(ct.c_uint)
c_bib_p = ct.POINTER(Biblioteca)

__pizzac__ = ct.CDLL("pizza.dll")
__pizzaSolver__ = __pizzac__.pizzaSolver
__pizzaSolver__.argtypes = [ct.c_uint, ct.c_uint, ct.c_uint, c_uint_p, c_bib_p, c_uint_p, c_uint_p, c_uint_p, c_uint_p]
__pizzaSolver__.restype = ct.c_uint


def pedirLibros(problema):
    idBibsC = ct.cast((ct.c_uint * problema.numBiblios.value)(), c_uint_p)
    nLibBibC = ct.cast((ct.c_uint * problema.numBiblios.value)(), c_uint_p)
    idLibBibC = ct.cast((ct.c_uint * (problema.numBiblios.value * problema.numLibros.value))(), c_uint_p)
    signUpNumRaw = ct.c_uint(0)
    score = int(__pizzaSolver__(problema.numLibros,
                                problema.numBiblios,
                                problema.numDias,
                                problema.valorLibros,
                                problema.bibliotecas,
                                idBibsC,
                                nLibBibC,
                                idLibBibC,
                                ct.byref(signUpNumRaw)))

    signUpNum = signUpNumRaw.value
    idBibs = np.array(idBibsC[:signUpNum])
    nLibBib = np.array(nLibBibC[:signUpNum])
    idLibBib = np.array([[idLibBibC[i*problema.numLibros.value+j] for j in range(nLibBib[i])] for i in range(signUpNum)])

    '''
    print ("signUpNum")
    print (signUpNum)
    print ("idBibs")
    print (idBibs)
    print ("nLibBib")
    print (nLibBib)
    print ("idLibBib")
    print (idLibBib)
    '''

    return score, signUpNum, idBibs, nLibBib, idLibBib

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

    print ("Parsing!")
    start = timer()
    try:
        problema = fh.loadBFile(input)
    except Exception as e:
        print (str(e))
        print ("Parse ended with errors!")
        traceback.print_stack()
        return
    end = timer()
    print("Time elapsed: %.4f seconds." % round(end-start, 4))
    print ("Starting!")
    start = timer()
    score, num_librerias, lista_librerias, num_libros_por_libreria, lista_libros_librerias = pedirLibros(problema)
    #print ("miau")
    #usedtyr, listtyr, scorer = pedirPizzaRandom(maxs, nty, values, niters, seed)
    # print ("miau")
    #if scorer > score:
    #    usedty = usedtyr
    #    listty = listtyr
    #    score = scorer
    end = timer()
    print("Done!")
    print("Time elapsed: %.4f seconds." % round(end-start, 4))
    print ("Score: " + str(score) + "/" + str(problema.maxValor))
    fh.saveBFile(output, num_librerias, lista_librerias, num_libros_por_libreria, lista_libros_librerias)

if __name__ == "__main__":
    main(sys.argv[1:])
