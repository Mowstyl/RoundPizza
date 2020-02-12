#ifndef __PIZZA_H
#define __PIZZA_H


/* Devuelve el numero de tipos en solution */
int pizzaSolver (int  maxval, // Maximo numero de porciones
                 int  ntypes, // Numero de tipos de pizza diferentes
                 int *valpertype, // Array con el valor de cada tipo
                 int *solution, // SALIDA. Se pasa ya inicializado. Vector que contendrá como mucho ntypes enteros
                 int *score); // SALIDA. Numero de porciones pedidas (suma del valor de los tipos en solution)

#endif
