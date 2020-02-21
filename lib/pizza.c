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

void
printArray (unsigned int *array,
            unsigned int  size)
{
  unsigned int i;

  printf ("[");
  if (size > 0)
    {
      printf ("%u", array[0]);
      for (i = 1; i < size; i++)
        printf (", %u", array[i]);
    }
  printf ("]");
}

void
printBib (Biblioteca *bib)
{
  printf ("Biblioteca %u\n", bib->id);
  printf ("\t%u libros\n", bib->nLibros);
  printf ("\t%u dias para registro\n", bib->diasReg);
  printf ("\t%u libros/dia\n", bib->libDia);
  printf ("\tLibros: ");
  printArray (bib->idLibros, bib->nLibros);
  printf ("\n");
}

/* Devuelve el score */
unsigned int
pizzaSolver (unsigned int  nLibros,     // Numero total de libros
             unsigned int  nBib,        // Numero de bibliotecas
             unsigned int  maxDias,     // Dias limite para escaneo
             unsigned int *scores,      // Array con el valor de cada libro
             Biblioteca   *bibs,        // Array de bibliotecas
             unsigned int *idBibs,      // idBibs[i] <- ids bibliotecas signupeadas en orden de signupeo
             unsigned int *nBookBib,    // nBookBib[i] <- numero de libros escaneados de biblioteca *idBibs[i]
             unsigned int *idBooksBib,  // idBooksBib[i] <- lista de ids de libros escaneados de biblioteca *idBibs[i]
             unsigned int *signUpNum)  // numero de bibliotecas signupeadas
{
  unsigned int *lectos, // La mascaraaaaaa
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

  lectos = (unsigned int*) calloc (nLibros, sizeof (unsigned int));
  biblios = (unsigned int*) calloc (nBib, sizeof (unsigned int));
  singuBib = 0;
  singuId = 0;
  remSingu = bibs->diasReg + 1;
  //printf ("%u libros y %u bibliotecas\n", nLibros, nBib);
  //printf ("Scores: ");
  //printArray (scores, nLibros);
  //printf ("\n");
  //printBib (bibs);
  for (dia = 0; dia < maxDias; dia++)
    {
      //printf ("\nDia %u/%u:\n", dia + 1, maxDias);
      //if (dia % 100 == 0)
      //  printf ("\nDia %u/%u:\n", dia + 1, maxDias);
      remSingu--;
      // SIGNUP
      if (remSingu == 0 && singuId < nBib)
        {
          //printf ("Finalizado Signupeo de %u.\n", (bibs + singuId)->id);
          idBibs[singuBib] = singuId;
          nBookBib[singuId] = 0;
          singuBib++;
          singuId++;
          if (singuId < nBib)
            {
              remSingu = (bibs + singuId)->diasReg;
              //printf ("Empezando Signupeo de %u.\n", (bibs + singuId)->id);
              //printBib (bibs + singuId);
            }
        }
      //else
      //  {
      //    if (singuId < nBib)
      //      printf ("Signupeo de %u: %u dias restantes\n", (bibs + singuId)->id, remSingu);
      //  }

      // SCAN
      for (i = 0; i < singuBib; i++)
        {
          if (biblios[i] == 0)
            {
              //printf ("Escaneando libros de %u.\n", (bibs + i)->id);
              for (j = 0; j < (bibs + i)->libDia; j++)
                {
                  //printf ("Lecidiendo\n");
                  b = primerNoLecto(lectos, bibs + i);
                  //printf ("Lecidido\n");

                  if (b == (bibs + i)->nLibros)
                    {
                      //printf ("No quedan libros en %u.\n", (bibs + i)->id);
                      biblios[i] = 1;
                      (bibs + i)->idLibros = (bibs + i)->idLibrosAux;
                      (bibs + i)->nLibros = (bibs + i)->nLibrosAux;
                      break;
                    }
                  else
                    {
                      //printf ("Escaneado libro %u.\n", (bibs + i)->idLibros[b]);
                      lectos[(bibs + i)->idLibros[b]] = 1;
                      idBooksBib[i * nLibros + nBookBib[i]] = (bibs + i)->idLibros[b];
                      nBookBib[i]++;
                      (bibs + i)->idLibros = (bibs + i)->idLibros + b + 1;
                      (bibs + i)->nLibros = (bibs + i)->nLibros - b - 1;
                    }
                }
              //printf ("Fin del escaneo de hoy en %u.\n", (bibs + i)->id);
            }
        }
      //printf ("Se acabo el dia\n");
    }
  //printf ("Fin simulacion!\n");

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
  //printf ("Obtenidos %d/%d\n", score, totscore);
  *signUpNum = singuBib;

  return score;
}

unsigned int
primerNoLecto (unsigned int *lectos,
               Biblioteca   *bib)
{
  unsigned int i;

  for (i = 0; i < bib->nLibros; i++)
    {
      //printf("Miau\n");
      //printf("forNOLECTO %u\n", bib->idLibros[i]);
      if (lectos[bib->idLibros[i]] == 0)
        break;
    }
  //printf("haLecido\n");

  return i;
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
