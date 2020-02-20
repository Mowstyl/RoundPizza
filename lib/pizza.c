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

/* Devuelve el numero de bibliotecas signupeadas */
int
pizzaSolver (int    nLibros,    // Numero total de libros
             int    maxDias,    // Dias limite para escaneo
             int   *scores,     // Array con el valor de cada libro
             int    nBib,       // Numero de bibliotecas
             int   *nLibBib,    // nlibbib[id] <- numero de libros en biblioteca id
             int   *heurBib,    // heurBib[id] <- heuristica de la biblioteca id
             int   *suDayBib,   // sudaybib[id] <- dias en realizar signup
             int   *boDayBib,   // bodaybib[id] <- libros a escanear por dia
             int   *libBib,     // libbib[id] <- lista de ids de libros disponibles en la biblioteca id
             int   *idBibs,     // *idBibs[i] <- ids bibliotecas signupeadas en orden de signupeo
             int   *nBookBib,   // *nBookBib[i] <- numero de libros escaneados de biblioteca *idBibs[i]
             int   *idBooksBib, // *idBooksBib[i] <- lista de ids de libros escaneados de biblioteca *idBibs[i]
             int   *signUpNum)  // numero de bibliotecas signupeadas
{
  int *lectos, // La mascaraaaaaa
      *biblios, // La mascaraaaaaa
       dia,
       singuBib, // Numero de bibliotecas singupeadas
       singuId, // ID de la biblioteca siendo singupeada
       remSingu, // Dias restantes para terminar el singu
       i,
       j,
       b,
       score,
       totscore;

  /*
  printf ("%d libros\n", nLibros);
  printf ("%d dias\n", maxDias);
  for (i = 0; i < nLibros; i++)
    printf ("%d, ", scores[i]);
  printf ("puntos\n");
  printf ("%d bibliotecas\n", nBib);
  for (i = 0; i < nBib; i++)
    printf ("%d, ", nLibBib[i]);
  printf ("lib/bib\n");
  for (i = 0; i < nBib; i++)
    printf ("%d, ", suDayBib[i]);
  printf ("dia/SIGNUP\n");
  for (i = 0; i < nBib; i++)
    printf ("%d, ", boDayBib[i]);
  printf ("lib/dia\n");
  for (i = 0; i < nBib; i++)
    {
      for (j = 0; j < nLibBib[i]; j++)
        printf ("%d, ", libBib[i*nBib + j]);
      printf ("libros en %d\n", i);
    }
  */

  lectos = (int*) calloc (nLibros, sizeof (int));
  biblios = (int*) calloc (nBib, sizeof (int));
  singuBib = -1;
  singuId = -1;
  remSingu = 0;
  for (dia = 0; dia < maxDias; dia++)
    {
      // SIGNUP
      if (remSingu == 0 && singuBib < nBib-1)
        {
          idBibs[singuBib] = singuId;
          singuBib++;
          singuId++;
          remSingu = suDayBib[singuId];
        }
      remSingu--;

      // SCAN
      for (i = 0; i < singuBib; i++)
        {
          if (biblios[i] == 0)
            {
              for (j = 0; j < boDayBib[i]; j++)
                {
                  b = mejorNoLecto(scores, lectos, nLibBib[i], libBib + i*nBib);

                  if (b == -1)
                    {
                      biblios[i] = 1;
                      break;
                    }
                  else
                    {
                      lectos[b] = 1;
                      nBookBib[i]++;
                      idBooksBib[i * singuBib + (nBookBib[i]-1)] = b;
                    }
                }
            }
        }
    }

  score = 0;
  totscore = 0;
  #pragma omp parallel shared (nLibros, lectos, scores, score, totscore) private (i)
    {
      #pragma omp for reduction (+:score)
      for (i = 0; i < nLibros; i++)
        {
          //printf("forPRAGMA\n");
          if (lectos[i] == 1)
            score += scores[i];
          totscore += scores[i];
        }
    }
  printf ("Obtenidos %d/%d\n", score, totscore);
  *signUpNum = singuBib;

  return score;
}

int
mejorNoLecto (int *scores,
              int *lectos,
              int  nLibBib,
              int *libBib)
{
  int i,
      primerId;

  primerId = -1;
  for (i = 0; i < nLibBib; i++)
    {
      //printf("forNOLECTO %d\n", libBib[i]);
      if (lectos[libBib[i]] == 0)
        {
          //printf("RECTO\n");
          primerId = libBib[i];
          break;
        }
    }
  //printf("haLecido\n");

  return primerId;
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

int
hillClimbing (int  *candidato,
              int   tamCandidato,
              int  *valpertype,
              int  *scoreCandidato,
              int (*score)         (int*,
                                    int,
                                    int*),
              int (*generavecinos) (int*,
                                    int,
                                    int***,
                                    int**))
{
  int **vecinos,
       *tamVecinos,
        nvecinos = generavecinos (candidato, tamCandidato, &vecinos, &tamVecinos),
        scoreI,
        i = 0,
        j;

  #pragma omp parallel default(none) shared (candidato, tamCandidato, scoreCandidato, score, generavecinos, vecinos, tamVecinos, nvecinos, scoreI, i, valpertype) private (j)
    {
      do
        {
          scoreI = score (vecinos[i], tamVecinos[i], valpertype);
          if (scoreI > *scoreCandidato)
            {
              free (candidato);
              tamCandidato = tamVecinos[i];
              *scoreCandidato = scoreI;
              candidato = (int*) malloc (tamCandidato * sizeof (int));
              #pragma omp for
              for (j = 0; j < tamCandidato; j++)
                candidato[j] = vecinos[i][j];
            }
          i++;
        } while (scoreI <= *scoreCandidato && i < nvecinos);

      #pragma omp for
      for (j = 0; j < nvecinos; j++)
        free (vecinos[j]);
    }
  free (vecinos);
  free (tamVecinos);

  return tamCandidato;
}

int
pizzaScore (int *sol,
            int  tamSol,
            int *valpertype)
{
  int i,
      score = 0;

  #pragma omp parallel default(none) shared (sol, tamSol, valpertype, score) private (i)
    {
      #pragma omp for reduction (+:score)
      for (i = 0; i < tamSol; i++)
        {
          score += valpertype[sol[i]];
        }
    }

  return score;
}

int
pizzaNeigh (int   *original,
            int    tamOrig,
            int ***vecinos,
            int  **tamVecinos)
{
  return *original + tamOrig + ***vecinos + **tamVecinos;
}
