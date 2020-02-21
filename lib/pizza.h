#ifndef __PIZZA_H
#define __PIZZA_H

struct LibraryStruct
{
  /* Identificador de esta biblioteca */
  unsigned int  id;
  /* Numero de libros en esta biblioteca */
  unsigned int  nLibros;
  unsigned int  nLibrosAux;
  /* Dias que tarda en realizar el signup */
  unsigned int  diasReg;
  /* Libros que se pueden sacar en un día */
  unsigned int  libDia;
  /* Array de ids de los libros disponibles en la biblioteca */
  unsigned int *idLibros;
  unsigned int *idLibrosAux;
};

typedef struct LibraryStruct Biblioteca;

/* Desordena un array aleatoriamente */
void shuffle    (int          *arr,        // Array a desordenar
                 size_t        n);          // Tamaño del array

/* Devuelve el score */
unsigned int pizzaSolver (unsigned int  nLibros,     // Numero total de libros
                          unsigned int  nBib,        // Numero de bibliotecas
                          unsigned int  maxDias,     // Dias limite para escaneo
                          unsigned int *scores,      // Array con el valor de cada libro
                          Biblioteca   *bibs,        // Array de bibliotecas
                          unsigned int *idBibs,      // idBibs[i] <- ids bibliotecas signupeadas en orden de signupeo
                          unsigned int *nBookBib,    // nBookBib[i] <- numero de libros escaneados de biblioteca *idBibs[i]
                          unsigned int *idBooksBib,  // idBooksBib[i] <- lista de ids de libros escaneados de biblioteca *idBibs[i]
                          unsigned int *signUpNum);  // numero de bibliotecas signupeadas

unsigned int primerNoLecto (unsigned int *lectos,
                            Biblioteca   *bib);

/* Devuelve el numero de tipos en solution */
int pizzaRandom (int           maxval,     // Maximo numero de porciones
                 int           ntypes,     // Numero de tipos de pizza diferentes
                 int          *valpertype, // Array con el valor de cada tipo
                 int          *solution,   // SALIDA. Se pasa ya inicializado. Vector que contendrá como mucho ntypes enteros
                 int          *score,      // SALIDA. Numero de porciones pedidas (suma del valor de los tipos en solution
                 int           niter,      // Numero de iteraciones aleatorias a realizar
                 unsigned int  seed);      // Semilla para el generador de números aleatorios

int hillClimbing (int   *candidato,
                  int    tamCandidato,
                  int   *valpertype,
                  int   *scoreCandidato,
                  int  (*score)         (int*,
                                         int,
                                         int*),
                  int  (*generavecinos) (int*,
                                         int,
                                         int***,
                                         int**));

int pizzaScore   (int   *sol,
                  int    tamSol,
                  int   *valpertype);

int pizzaNeigh   (int   *original,
                  int    tamOrig,
                  int ***vecinos,
                  int  **tamVecinos);

#endif
