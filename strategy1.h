#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

// Parallel Programm for computing LU decomposition
// Using 'parallel for' construct
/*
void crout_strategy1(double **A, double **L, double **U, int n) {   //pragma omp parallel for

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        U[i][i] = 1;
    }

    for (int j = 0; j < n; j++) {

        double sum_arr[n-j];
        #pragma omp parallel for
        for(int h=0; h<(n-j); h++){
            sum_arr[h] = 0.0;
        }


        #pragma omp parallel for collapse(2)
        for (int i = j; i < n; i++) {
            for (int k = 0; k < j; k++) {
                double value = L[i][k] * U[k][j];
                #pragma omp critical
                {
                  sum_arr[i-j] = sum_arr[i-j] + value;
                }
            }
        }

        // for(int h=0; h<(n-j); h++){
        //     // printf("Sum1 = %lf\n", sum_arr[h]);
        // }

        #pragma omp parallel for
        for(int h=0; h<(n-j); h++){
            L[h+j][j] = A[h+j][j] - sum_arr[h];
        }


        #pragma omp parallel for
        for(int h=0; h<(n-j); h++){
            sum_arr[h] = 0;
        }

        if (L[j][j] == 0) {
            exit(0);
        }

        #pragma omp parallel for collapse(2)
        for (int i = j; i < n; i++) {
            for(int k = 0; k < j; k++) {
                double value = L[j][k] * U[k][i];
                #pragma omp critical
                {
                  sum_arr[i-j] = sum_arr[i-j] + value;
                }
            }
        }

        #pragma omp parallel for
        for(int h=0; h<(n-j); h++){
            U[j][h+j] = (A[j][h+j] - sum_arr[h]) / L[j][j];
        }

    }
}
*/

void crout_strategy1(double **A, double **L, double **U, int n) {
    //int i, j, k;
    //double sum = 0;
    
    #pragma omp parallel for
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
          L[i][j] = 0;
          U[i][j] = 0;
      }
    }
    #pragma omp barrier
    
    
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        U[i][i] = 1;
    }
    #pragma omp barrier

    
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
//                double value1 = L[i][k] * U[k][j];
//                double value2 = L[j][k] * U[k][i];
                sum1 += L[i][k] * U[k][j];
                sum2 += L[j][k] * U[k][i];
            }
            L[i][j] = A[i][j] - sum1;
            U[j][i] = (A[j][i] - sum2) / L[j][j];
        }
        #pragma omp barrier
        
    }
}
