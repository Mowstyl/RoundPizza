 #!/usr/bin/python

import numpy as np
import heapq
import sys
import pickle
import os
from libreria import libreria
from libreria import Heap

# In this file we have the methods to parse the input file

def get_first(item_list):
    return heapq.heappop(item_list)

def insert_item(item_list, item):
    heapq.heappush(item_list, item)

def loadPFile(filepath):
    lista_scores = []
    lista_librerias = []
    heap_librerias = Heap()

    n_lines = 1
    separator = " "

    # if (not os.path.exists(filepath + ".pickle")):
    f = open(filepath, "r")
    if f == None:
        raise ValueError("File not found!")
    first_line = f.readline().split(separator)
    if len(first_line) != 3:
        raise ValueError('Bad formatted file!')
    try:
        num_books, num_libraries, num_days = [int(x) for x in first_line]
    except:
        raise ValueError('Must be integers!')
    if num_books < 1 or num_books > 10**5 or num_libraries < 1 or num_libraries > 10**5 or num_days < 1 or num_days > 10**5:
        raise ValueError('Limits error')

    # Leer scores de libros
    line = f.readline()
    try:
        lista_scores = list(map(int, line.split(separator)))
    except:
        raise ValueError('Must be integers!')

    # Leer datos de cada libreria
    for i in range(num_libraries):
        # Linea 1: numero de libros, dias de registro, libros por dia
        library_book_list = []
        line = f.readline().split(separator)
        try:
            library_num_books, signup_days, books_per_day = [int(x) for x in line]
        except:
            raise ValueError('Must be integers!')

        if library_num_books < 1 or library_num_books > 10**5 or signup_days < 1 or signup_days > 10**5 or books_per_day < 1 or books_per_day > 10**5:
            raise ValueError('Limits error')

        #Linea 2: libros en la libreria
        line = f.readline()
        try:
            library_book_list = list(map(int, line.split(separator)))
        except:
            raise ValueError('Must be integers!')

        # CONSTRUIR CLASE Y AÑADIR A LISTA DE LIBRERIAS
        library_book_list_scores = map(lambda x: lista_scores[x], library_book_list)
        library_to_add = libreria(i,
                                    library_num_books,
                                    signup_days,
                                    books_per_day,
                                    library_book_list,
                                    library_book_list_scores,
                                    num_days)

        # Insertar en heap para ordenar
        heap_librerias.insert_item(library_to_add)

#    else:
#        with open(filepath+".pickle", "rb") as handle:
#

    # ORDENACION DE LIBRERIAS
    for i in range(num_libraries):
        first = heap_librerias.get_first()
        lista_librerias.append(first)

    return (num_books, num_libraries, num_days, lista_scores, lista_librerias)

    # for i in range(n_lines):
        # line = f.readline()
        # arr = list(map(int, line.split(separator)))
        #for e in arr:
            #insert_item(items, e)
    #for e in range(len(items)):
        #print(get_first(items))
    #return max_slices, types_pizza, arr

#loadPFile(sys.argv[1])


def savePFile(filepath, num_librerias, lista_librerias, num_libros_por_libreria, lista_libros_librerias):
    f = open(filepath, "w+")
    # Sanity check: numero correcto de librerias
    if (num_librerias != len(lista_libros_librerias)):
        raise ValueError("Numero incorrecto de librerias")

    f.write(str(num_librerias) + '\n')
    for i in range(num_librerias):
        f.write(str(lista_librerias[i]) + ' ' + str(num_libros_por_libreria[i]) + '\n')
        for j in range(num_libros_por_libreria[i] - 1):
            f.write(str(lista_libros_librerias[i][j]) + ' ')
        f.write(str(lista_libros_librerias[i][num_libros_por_libreria[i] - 1]) + '\n')

    f.close()


    # f.write(str(n_types) + '\n')
    # for i in range(len(list_types)-1):
    #     f.write(str(list_types[i]) + ' ')
    # f.write(str(list_types[len(list_types)-1]))
    # f.close()

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
