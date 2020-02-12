#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <time.h>
#include <omp.h>
#include "pizza.h"

/* Devuelve el numero de tipos en solution */
int
pizzaSolver (int  maxval,      // Maximo numero de porciones
             int  ntypes,      // Numero de tipos de pizza diferentes
             int *valpertype,  // Array con el valor de cada tipo
             int *solution,    // SALIDA. Se pasa ya inicializado. Vector que contendrá como mucho ntypes enteros
             int *score)       // SALIDA. Numero de porciones pedidas (suma del valor de los tipos en solution)
{
  int i,
      currenttypes = 0,
      currentval = 0;

  for (i = ntypes - 1; i >= 0; i--)
    {
      if (valpertype[i] + currentval <= maxval)
        {
          solution[currenttypes] = i;
          currenttypes++;
          currentval += valpertype[i];
        }
    }
  *score = currentval;

  return currenttypes;
}
