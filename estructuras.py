import ctypes as ct

class Biblioteca(ct.Structure):
    _fields_ = [("id", ct.c_uint),
                ("nLibros", ct.c_uint),
                ("nLibrosAux", ct.c_uint),
                ("diasReg", ct.c_uint),
                ("libDia", ct.c_uint),
                ("idLibros", ct.POINTER(ct.c_uint)),
                ("idLibrosAux", ct.POINTER(ct.c_uint))]

    def __init__(self, id, nLibros, diasReg, libDia, idLibros):
        self.id = ct.c_uint(id)
        self.nLibros = ct.c_uint(nLibros)
        self.nLibrosAux = self.nLibros
        self.diasReg = ct.c_uint(diasReg)
        self.libDia = ct.c_uint(libDia)
        array_libs = ct.c_uint * nLibros
        self.idLibros = ct.cast((ct.c_uint * nLibros)(*idLibros), ct.POINTER(ct.c_uint))
        self.idLibrosAux = self.idLibros
        '''
        if id == 0:
            print("YAMAHA")
            print(idLibros)
            print("MISTUBITSI")
            print(self.idLibros[:nLibros])
            print("HONDA")
        '''

class Problema():
    def __init__(self, numLibros, numBiblios, numDias, valorLibros, maxValor, bibliotecas):
        self.numLibros = ct.c_uint(numLibros)
        self.numBiblios = ct.c_uint(numBiblios)
        self.numDias = ct.c_uint(numDias)
        self.valorLibros = ct.cast((ct.c_uint * numLibros)(*valorLibros), ct.POINTER(ct.c_uint))
        self.maxValor = maxValor
        self.bibliotecas = ct.cast((Biblioteca * numBiblios)(*bibliotecas), ct.POINTER(Biblioteca))
