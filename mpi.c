#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strategy4(double **A, double **L, double **U, int n, int my_rank, int comm_sz) {

    for (int j = 0; j < n; j++) {

        for (int i = j; i < n; i++) {
            if(i%comm_sz == my_rank)
            {
                double value = 0;
                for (int k = 0; k < j; k++) {
                   value += L[i][k] * U[k][j];
                }
                L[i][j] = A[i][j] - value;
            }
            MPI_Bcast(&L[i][j], 1, MPI_DOUBLE, i%comm_sz, MPI_COMM_WORLD);
        }
        for (int i = j; i < n; i++) {
            if(i%comm_sz == my_rank)
            {
                if (L[j][j] == 0) {
                    exit(0);
                }
                double value = 0;
                for(int k = 0; k < j; k++) {
                    value += L[j][k] * U[k][i];
                }
                U[j][i] = (A[j][i] - value) / L[j][j];
            }
            MPI_Bcast(&U[j][i], 1, MPI_DOUBLE, i%comm_sz, MPI_COMM_WORLD);
        }
    }
}

int main(int argc, char *argv[]){
  // taking input from command line
  int n = atoi(argv[1]); // Number of rows and columns of square matrix A
    //printf("%d  \n",n);
  char *input_file = argv[2]; // File that contains square matrix A
    //printf("%s",input_file);
  int num_threads = atoi(argv[3]);  // Number of threads of be run in parallel program
  int strategy = 4;
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

    for (int i = 0; i < n; i++) {
         U[i][i] = 1;
    }
    // double start = MPI_Wtime();
    MPI_Init(NULL, NULL);
    int comm_sz ;
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    strategy4(A, L, U, n, my_rank, comm_sz);

    MPI_Finalize();

    // double end = MPI_Wtime();

    // printf("Time took by parallel part %f seconds\n", end - start);
    if(my_rank == 0){

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
        if(i != n-1)
          fprintf(lfptr, "\n");
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

    }

    return 0;
}
