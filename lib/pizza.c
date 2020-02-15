#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#define _THREAD_SAFE

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "pizza.h"


/* Desordena un array aleatoriamente */
void
shuffle (int          *arr,   // Array a desordenar
         size_t        n)     // Tamaño del array
{
  if (n > 1)
    {
      size_t i;
      //printf ("{");
      for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
          //printf ("%d, ", arr[i]);
        }
      //printf ("}\n");
    }
}

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

/* Devuelve el numero de tipos en solution */
int
pizzaRandom (int           maxval,      // Maximo numero de porciones
             int           ntypes,      // Numero de tipos de pizza diferentes
             int          *valpertype,  // Array con el valor de cada tipo
             int          *solution,    // SALIDA. Se pasa ya inicializado. Vector que contendrá como mucho ntypes enteros
             int          *score,       // SALIDA. Numero de porciones pedidas (suma del valor de los tipos en solution
             int           niter,       // Numero de iteraciones aleatorias a realizar
             unsigned int  seed)        // Semilla para el generador de números aleatorios
{
  int   i,
        j,
        best,
       *typeth,
       *ntypess = (int*) malloc (niter * sizeof (int)),
       *scores = (int*) malloc (niter * sizeof (int)),
      **sols = (int**) malloc (niter * sizeof (int*));
  //unsigned int thseed;
  srand (seed);
  //printf ("Ninja\n");

  #pragma omp parallel default(none) shared (maxval, ntypes, valpertype, solution, score, niter, seed, ntypess, scores, best, sols) private (i, j, typeth)
    {
      #pragma omp for
      for (i = 0; i < niter; i++)
        {
          //thseed = seed + i;
          ntypess[i] = 0;
          scores[i] = 0;
          sols[i] = (int*) malloc (ntypes * sizeof (int));
          typeth = (int*) malloc (ntypes * sizeof (int));
          //printf ("Reserved %d\n", omp_get_thread_num());

          for (j = 0; j < ntypes; j++)
            {
              typeth[j] = j;
            }
          //printf ("Shuffling %d\n", omp_get_thread_num());
          shuffle (typeth, ntypes);
          //printf ("Shuffled %d\n", omp_get_thread_num());

          for (j = 0; j < ntypes; j++)
            {
              if (valpertype[typeth[j]] + scores[i] <= maxval)
                {
                  sols[i][ntypess[i]] = typeth[j];
                  ntypess[i]++;
                  scores[i] += valpertype[typeth[j]];
                }
            }
          //printf ("Solutioned %d\n", omp_get_thread_num());
          free (typeth);
          //printf ("Ended %d\n", omp_get_thread_num());
        }
    }

  //printf ("END OF PARALLEL\n");

  *score = scores[0];
  best = 0;

  for (i = 1; i < niter; i++)
    {
      if (scores[i] > *score)
        {
          *score = scores[i];
          best = i;
        }
    }

  for (i = 0; i < ntypess[best]; i++)
    {
      solution[i] = sols[best][i];
    }
  best = ntypess[best];
  //printf ("Got best\n");

  for (i = 0; i < niter; i++)
    {
      free (sols[i]);
    }
  free (sols);
  free (scores);
  free (ntypess);
  //printf ("Fred all\n");

  return best;
}
