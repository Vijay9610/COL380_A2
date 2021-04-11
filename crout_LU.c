#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

// Sequential Programm for computing LU decomposition
void crout_sequential(double **A, double **L, double **U, int n) {
    int i, j, k;
    double sum = 0;
    for (i = 0; i < n; i++) {
        U[i][i] = 1;
    }

    for (j = 0; j < n; j++) {
        for (i = j; i < n; i++) {
            sum = 0;
            for (k = 0; k < j; k++) {
                sum = sum + L[i][k] * U[k][j];
            }
            L[i][j] = A[i][j] - sum;
        }
        for (i = j; i < n; i++) {
            sum = 0;
            for(k = 0; k < j; k++) {
                sum = sum + L[j][k] * U[k][i];
            }
            if (L[j][j] == 0) {
                exit(0);
            }
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }


}

int main(int argc, char *argv[]) {

  // taking input from command line
  int n = atoi(argv[1]); // Number of rows and columns of square matrix A
  char *input_file = argv[2]; // File that contains square matrix A
  int num_threads = atoi(argv[3]);  // Number of threads of be run in parallel program
  int strategy = atoi(argv[4]); // parallel strategy

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

  // Printing input matrix
  printf("Input matrix A: \n");
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      printf("%0.3lf ", A[i][j]);
    }
    printf("\n");
  }

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
    crout_sequential(A, L, U, n);
  }


  // Printing L matrix
  printf("matrix L: \n");
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      printf("%0.3lf ", L[i][j]);
    }
    printf("\n");
  }

  // Printing input matrix
  printf("matrix U: \n");
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      printf("%0.3lf ", U[i][j]);
    }
    printf("\n");
  }


  return 0;
}
