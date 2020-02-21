 #!/usr/bin/python

import numpy as np
import sys
import os
from estructuras import Biblioteca, Problema


def loadBFile(filepath):
    numLibros = 0
    numBiblios = 0
    numDias = 0
    valorLibros = None

    n_lines = 1
    separator = " "

    with open(filepath, "r") as f:
        if f == None:
            raise ValueError("File not found!")
        first_line = f.readline().split(separator)
        if len(first_line) != 3:
            raise ValueError('Bad formatted file!')
        try:
            numLibros, numBiblios, numDias = [int(x) for x in first_line]
        except:
            raise ValueError('Must be integers!')
        if not (1 <= numLibros <= 10**5) or not (1 <= numBiblios <= 10**5) or not (1 <= numDias <= 10**5):
            raise ValueError('Limits error')

        # Leer scores de libros
        line = f.readline()
        try:
            valorLibros = np.array(list(map(int, line.split(separator))))
        except:
            raise ValueError('Must be integers!')

        maxValor = valorLibros.sum()
        bibliotecas = []
        # Leer datos de cada libreria
        for i in range(numBiblios):
            bLibNum = 0
            diasSU = 0
            libDia = 0
            listaLibros = None
            # Linea 1: numero de libros, dias de registro, libros por dia
            line = f.readline().split(separator)
            try:
                bLibNum, diasSU, libDia = (int(x) for x in line)
            except:
                raise ValueError('Must be integers!')

            if not (1 <= bLibNum <= 10**5) or not (1 <= diasSU <= 10**5) or not (1 <= libDia <= 10**5):
                raise ValueError('Limits error')

            #Linea 2: libros en la libreria
            line = f.readline()
            try:
                listaLibros = np.array(list(map(int, line.split(separator))))
            except:
                raise ValueError('Must be integers!')

            # CONSTRUIR CLASE Y AÑADIR A LISTA DE LIBRERIAS
            bibliotecas.append(Biblioteca(i, bLibNum, diasSU, libDia, listaLibros))

    return Problema(numLibros, numBiblios, numDias, valorLibros, maxValor, bibliotecas)


def saveBFile(filepath, num_librerias, lista_librerias, num_libros_por_libreria, lista_libros_librerias):
    with open(filepath, "w+") as f:
        # Sanity check: numero correcto de librerias
        if (num_librerias != len(lista_libros_librerias)):
            raise ValueError("Numero incorrecto de librerias")

        f.write(str(np.count_nonzero(num_libros_por_libreria)) + '\n')
        for i in range(num_librerias):
            if num_libros_por_libreria[i] > 0:
                f.write(str(lista_librerias[i]) + ' ' + str(num_libros_por_libreria[i]) + '\n')
                for j in range(num_libros_por_libreria[i] - 1):
                    f.write(str(lista_libros_librerias[i][j]) + ' ')
                f.write(str(lista_libros_librerias[i][num_libros_por_libreria[i] - 1]) + '\n')
