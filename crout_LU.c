#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#include "strategy0.h"
#include "strategy1.h"
#include "strategy2.h"
#include "strategy3.h"


int main(int argc, char *argv[]) {

  // printf("Hii\n");
  // taking input from command line
  int n = atoi(argv[1]); // Number of rows and columns of square matrix A
  char *input_file = argv[2]; // File that contains square matrix A
  int num_threads = atoi(argv[3]);  // Number of threads of be run in parallel program
  int strategy = atoi(argv[4]); // parallel strategy
  // printf("Hii\n");
  // Initializing the matrix A
  double** A = malloc(n * sizeof(double*));
  for(int i=0; i<n; i++){
    A[i] = malloc(n * sizeof(double*));
  }

  // Reading input from the file
  FILE *infile;
  infile = fopen(input_file, "r");
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(!fscanf(infile, "%lf", &A[i][j]))
        break;
    }
  }

  fclose(infile);


  // Initializing the matrix L
  double** L = malloc(n * sizeof(double*));
  for(int i=0; i<n; i++){
    L[i] = malloc(n * sizeof(double*));
  }

  // Initializing the matrix U
  double** U = malloc(n * sizeof(double*));
  for(int i=0; i<n; i++){
    U[i] = malloc(n * sizeof(double*));
  }

  // Strategy 0 --- Using Sequential program for computation
  if(strategy == 0){
    omp_set_num_threads(num_threads);
    // double start = omp_get_wtime();
    crout_sequential(A, L, U, n);
    // double end = omp_get_wtime();

    // printf("Time took by Sequential part %f seconds\n", end - start);
  }
  else if(strategy == 1){
    // Strategy 1 --- Parallelization using 'parallel for'
    omp_set_num_threads(num_threads);
    // double start = omp_get_wtime();
    crout_strategy1(A, L, U, n);
    // double end = omp_get_wtime();


    // printf("Time took by parallel part %f seconds\n", end - start);

  }
  else if(strategy == 2){

    // Strategy 2 --- Parallelization using 'sections'
    omp_set_num_threads(num_threads);
    // double start = omp_get_wtime();
    crout_strategy2(A, L, U, n);
    // double end = omp_get_wtime();

    // printf("Time took by parallel part %f seconds\n", end - start);
  }
  else{ /*strategy == 3*/
    omp_set_num_threads(num_threads);
    // double start = omp_get_wtime();
    crout_strategy3(A, L, U, n, num_threads);
    // double end = omp_get_wtime();

    // printf("Time took by parallel part %f seconds\n", end - start);
  }


  // Writting output into text files
  FILE *lfptr, *ufptr;

  // Paths to output files
  char lpath[100] = "./output_L";
  char buf1[5];
  // itoa(strategy, buf1, 10);
  sprintf(buf1, "%d", strategy);
  // char str2[] = buf1;
  char str3[] = "_";
  char buf2[5];
  // itoa(num_threads, buf2, 10);
  sprintf(buf2, "%d", num_threads);
  // char str4[] = buf2;
  char str5[] = ".txt";
  char upath[100] = "./output_U";

  char temp[50] = "_";
  strcat(temp, buf1);
  strcat(temp, str3);
  strcat(temp, buf2);
  strcat(temp, str5);

  strcat(lpath, temp);
  strcat(upath, temp);

  // printf("lpath = %s\n", lpath);
  // printf("upath = %s\n", upath);

  lfptr = fopen(lpath, "w");
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      fprintf(lfptr, "%0.12f ", L[i][j]);
    }

    if(i != n-1){
      fprintf(lfptr, "\n");
    }

  }
  fclose(lfptr);

  ufptr = fopen(upath, "w");
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      fprintf(ufptr, "%0.12f ", U[i][j]);
    }
    if(i != n-1)
      fprintf(ufptr, "\n");
  }
  fclose(ufptr);



  return 0;
}
