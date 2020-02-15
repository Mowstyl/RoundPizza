#ifndef __PIZZA_H
#define __PIZZA_H

/* Desordena un array aleatoriamente */
void shuffle    (int          *arr,        // Array a desordenar
                 size_t        n);          // Tamaño del array

/* Devuelve el numero de tipos en solution */
int pizzaSolver (int           maxval,     // Maximo numero de porciones
                 int           ntypes,     // Numero de tipos de pizza diferentes
                 int          *valpertype, // Array con el valor de cada tipo
                 int          *solution,   // SALIDA. Se pasa ya inicializado. Vector que contendrá como mucho ntypes enteros
                 int          *score);     // SALIDA. Numero de porciones pedidas (suma del valor de los tipos en solution)

/* Devuelve el numero de tipos en solution */
int pizzaRandom (int           maxval,     // Maximo numero de porciones
                 int           ntypes,     // Numero de tipos de pizza diferentes
                 int          *valpertype, // Array con el valor de cada tipo
                 int          *solution,   // SALIDA. Se pasa ya inicializado. Vector que contendrá como mucho ntypes enteros
                 int          *score,      // SALIDA. Numero de porciones pedidas (suma del valor de los tipos en solution
                 int           niter,      // Numero de iteraciones aleatorias a realizar
                 unsigned int  seed);      // Semilla para el generador de números aleatorios

#endif
