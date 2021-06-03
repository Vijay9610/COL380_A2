#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

// Function for recursevely Initializing U matrix using 'sections' construct
void recurse_init_U(int start, int end, int threads, double **U, int n){
  if(threads > n)
    threads = n;
  if(threads == 1){
    for(int i=start; i <= end; i++){
      U[i][i] = 1;
    }
  }
  else{
    #pragma omp parallel sections
    {
      #pragma omp section
      {
        recurse_init_U(start, end/2, threads/2, U, n);
      }
      #pragma omp section
      {
        recurse_init_U(end/2+1, end, threads/2, U, n);
      }
    }
  }
}

void parallelise_function(double **A, double **L, double **U, int n, int num_threads, int i_start, int i_end, int j){
    
    #pragma omp parallel for num_threads(num_threads)
    for (int i = i_start; i < i_end; i++) {
        double sum1 = 0;
        double sum2 = 0;
        for (int k = 0; k < j; k++) {
            sum1 += L[i][k] * U[k][j];
            sum2 += L[j][k] * U[k][i];
        }
        L[i][j] = A[i][j] - sum1;
        U[j][i] = (A[j][i] - sum2) / L[j][j];
    }
    #pragma omp barrier
    
}

// Parallel program for computing LU decomposition
// Using both 'parallel for' and 'parallel sections' constructs
/*
void crout_strategy3(double **A, double **L, double **U, int n, int num_threads){
    
  omp_set_max_active_levels(1);
  recurse_init_U(0, n-1, num_threads, U, n);

  for (int j = 0; j < n; j++) {
          
          int i=j;
          double sum = 0;
          for (int k = 0; k < j; k++) {
              double value = L[i][k] * U[k][j];
              sum += value;
          }
          L[i][j] = A[i][j] - sum;
          
          if(L[j][j] == 0){
              exit(0);
          }
          
          if(num_threads == 1){
              for (int i = j; i < n; i++) {
                  double sum1 = 0;
                  double sum2 = 0;
                  for (int k = 0; k < j; k++) {
                      sum1 += L[i][k] * U[k][j];
                      sum2 += L[j][k] * U[k][i];
                  }
                  L[i][j] = A[i][j] - sum1;
                  U[j][i] = (A[j][i] - sum2) / L[j][j];
              }
          }
          else{
              #pragma omp sections
              {
                #pragma omp section
                {
                    parallelise_function(A, L, U, n, num_threads/2, j, (n-j)/2, j);
                }
                #pragma omp section
                {
                    parallelise_function(A, L, U, n, num_threads/2, (n-j)/2, n, j);
                }
              }
              
          }
  }
}
*/


void crout_strategy3(double **A, double **L, double **U, int n, int num_threads){
  
  #pragma omp sections
  {
      #pragma omp section
      {
          for(int i=0; i<n/8; i++){
            for(int j=0; j<n; j++){
                L[i][j] = 0;
                U[i][j] = 0;
            }
          }
      }
      #pragma omp section
      {
          for(int i=n/8; i<2*n/8; i++){
            for(int j=0; j<n; j++){
                L[i][j] = 0;
                U[i][j] = 0;
            }
          }
      }
      #pragma omp section
      {
          for(int i=2*n/8; i<3*n/8; i++){
            for(int j=0; j<n; j++){
                L[i][j] = 0;
                U[i][j] = 0;
            }
          }
      }
      #pragma omp section
      {
          for(int i=3*n/8; i<4*n/8; i++){
            for(int j=0; j<n; j++){
                L[i][j] = 0;
                U[i][j] = 0;
            }
          }
      }
      #pragma omp section
      {
          for(int i=4*n/8; i<5*n/8; i++){
            for(int j=0; j<n; j++){
                L[i][j] = 0;
                U[i][j] = 0;
            }
          }
      }
      #pragma omp section
      {
          for(int i=5*n/8; i<6*n/8; i++){
            for(int j=0; j<n; j++){
                L[i][j] = 0;
                U[i][j] = 0;
            }
          }
      }
      #pragma omp section
      {
          for(int i=6*n/8; i<7*n/8; i++){
            for(int j=0; j<n; j++){
                L[i][j] = 0;
                U[i][j] = 0;
            }
          }
      }
      #pragma omp section
      {
          for(int i=7*n/8; i<n; i++){
            for(int j=0; j<n; j++){
                L[i][j] = 0;
                U[i][j] = 0;
            }
          }
      }
  }

  omp_set_max_active_levels(1);
  recurse_init_U(0, n-1, num_threads, U, n);

  for (int j = 0; j < n; j++) {
          
          int i=j;
          double sum = 0;
          for (int k = 0; k < j; k++) {
              double value = L[i][k] * U[k][j];
              sum += value;
          }
          L[i][j] = A[i][j] - sum;
          
          if(L[j][j] == 0){
              exit(0);
          }
          
          #pragma omp parallel for
          for (int i = j; i < n; i++) {
            double sum1 = 0;
            double sum2 = 0;
            for (int k = 0; k < j; k++) {
                sum1 += L[i][k] * U[k][j];
                sum2 += L[j][k] * U[k][i];
            }
            L[i][j] = A[i][j] - sum1;
            U[j][i] = (A[j][i] - sum2) / L[j][j];
          }
          #pragma omp barrier
      
  }
}

