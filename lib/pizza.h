#ifndef __PIZZA_H
#define __PIZZA_H

/* Desordena un array aleatoriamente */
void shuffle    (int          *arr,        // Array a desordenar
                 size_t        n);          // Tamaño del array

/* Devuelve el score */
int pizzaSolver (int           nLibros,     // Numero total de libros
                 int           maxDias,     // Dias limite para escaneo
                 int          *scores,      // Array con el valor de cada libro
                 int           nBib,        // Numero de bibliotecas
                 int          *nLibBib,     // nlibbib[id] <- numero de libros en biblioteca id
                 int          *heurBib,     // heurBib[id] <- heuristica de la biblioteca id
                 int          *suDayBib,    // sudaybib[id] <- dias en realizar signup
                 int          *boDayBib,    // bodaybib[id] <- libros a escanear por dia
                 int          *libBib,      // libbib[id] <- lista de ids de libros disponibles en la biblioteca id
                 int          *idBibs,      // idBibs[i] <- ids bibliotecas signupeadas en orden de signupeo
                 int          *nBookBib,    // nBookBib[i] <- numero de libros escaneados de biblioteca *idBibs[i]
                 int          *idBooksBib,  // idBooksBib[i] <- lista de ids de libros escaneados de biblioteca *idBibs[i]
                 int          *signUpNum);  // numero de bibliotecas signupeadas

int mejorNoLecto (int *scores,
                  int *lectos,
                  int  nLibBib,
                  int *libBib);

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
