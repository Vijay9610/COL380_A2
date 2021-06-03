#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

// Parallel Programm for computing LU decomposition
// Using 'sections' construct
/*
void crout_strategy2(double **A, double **L, double **U, int n) {

    double sum = 0;

    #pragma omp parallel sections
    {
      #pragma omp section
      {
        for(int i=0; i<n/8; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=n/8; i<2*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=2*n/8; i<3*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=3*n/8; i<4*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=4*n/8; i<5*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=5*n/8; i<6*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=6*n/8; i<7*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=7*n/8; i < n ; i++){
          U[i][i] = 1;
        }
      }
    }



    for (int j = 0; j < n; j++) {

        for (int i = j; i < n; i++) {
            sum = 0;

            #pragma omp parallel sections
            {
              #pragma omp section
              {
                double local_sum = 0;
                for (int k = 0; k <= j/8-1; k++) {
                    local_sum = local_sum + L[i][k] * U[k][j];
                }
                #pragma omp critical
                  {sum = sum + local_sum;}
              }

              #pragma omp section
              {
                double local_sum = 0;
                for (int k = j/8; k <= 2*j/8-1; k++) {
                    local_sum = local_sum + L[i][k] * U[k][j];
                }
                #pragma omp critical
                  {sum = sum + local_sum;}
              }

              #pragma omp section
              {
                double local_sum = 0;
                for (int k = 2*j/8; k <= 3*j/8-1; k++) {
                    local_sum = local_sum + L[i][k] * U[k][j];
                }
                #pragma omp critical
                sum = sum + local_sum;
              }

              #pragma omp section
              {
                double local_sum = 0;
                for (int k = 3*j/8; k <= 4*j/8-1; k++) {
                    local_sum = local_sum + L[i][k] * U[k][j];
                }
                #pragma omp critical
                sum = sum + local_sum;
              }

              #pragma omp section
              {
                double local_sum = 0;
                for (int k = 4*j/8; k <= 5*j/8-1; k++) {
                    local_sum = local_sum + L[i][k] * U[k][j];
                }
                #pragma omp critical
                {sum = sum + local_sum;}
              }

              #pragma omp section
              {
                double local_sum = 0;
                for (int k = 5*j/8; k <= 6*j/8-1; k++) {
                    local_sum = local_sum + L[i][k] * U[k][j];
                }
                #pragma omp critical
                {sum = sum + local_sum;}
              }

              #pragma omp section
              {
                double local_sum = 0;
                for (int k = 6*j/8; k <= 7*j/8-1; k++) {
                    local_sum = local_sum + L[i][k] * U[k][j];
                }
                #pragma omp critical
                {sum = sum + local_sum;}
              }

              #pragma omp section
              {
                double local_sum = 0;
                for (int k = 7*j/8; k <= j-1; k++) {
                    local_sum = local_sum + L[i][k] * U[k][j];
                }
                #pragma omp critical
                {sum = sum + local_sum;}
              }
            }

            L[i][j] = A[i][j] - sum;
        }

        for (int i = j; i < n; i++) {
          sum = 0;
          
         // for (int k = 0; k < j; k++) {
         //    sum = sum + L[j][k] * U[k][j];
         // }

          #pragma omp sections
          {
            #pragma omp section
            {
              double local_sum = 0;
              for (int k = 0; k <= j/8-1; k++) {
                  local_sum = local_sum + L[j][k] * U[k][i];
              }
              #pragma omp critical
              {sum = sum + local_sum;}
            }

            #pragma omp section
            {
              double local_sum = 0;
              for (int k = j/8; k <= 2*j/8-1; k++) {
                  local_sum = local_sum + L[j][k] * U[k][i];
              }
              #pragma omp critical
              {sum = sum + local_sum;}
            }

            #pragma omp section
            {
              double local_sum = 0;
              for (int k = 2*j/8; k <= 3*j/8-1; k++) {
                  local_sum = local_sum + L[j][k] * U[k][i];
              }
              #pragma omp critical
              {sum = sum + local_sum;}
            }

            #pragma omp section
            {
              double local_sum = 0;
              for (int k = 3*j/8; k <= 4*j/8-1; k++) {
                  local_sum = local_sum + L[j][k] * U[k][i];
              }
              #pragma omp critical
              {sum = sum + local_sum;}
            }

            #pragma omp section
            {
              double local_sum = 0;
              for (int k = 4*j/8; k <= 5*j/8-1; k++) {
                  local_sum = local_sum + L[j][k] * U[k][i];
              }
              #pragma omp critical
              {sum = sum + local_sum;}
            }

            #pragma omp section
            {
              double local_sum = 0;
              for (int k = 5*j/8; k <= 6*j/8-1; k++) {
                  local_sum = local_sum + L[j][k] * U[k][i];
              }
              #pragma omp critical
              {sum = sum + local_sum;}
            }

            #pragma omp section
            {
              double local_sum = 0;
              for (int k = 6*j/8; k <= 7*j/8-1; k++) {
                  local_sum = local_sum + L[j][k] * U[k][i];
              }
              #pragma omp critical
              {sum = sum + local_sum;}
            }

            #pragma omp section
            {
              double local_sum = 0;
              for (int k = 7*j/8; k <= j-1; k++) {
                  local_sum = local_sum + L[j][k] * U[k][i];
              }
              #pragma omp critical
              {sum = sum + local_sum;}
            }
          }
            if (L[j][j] == 0) {
                exit(0);
            }
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }
}
*/

void crout_strategy2(double **A, double **L, double **U, int n) {

    double sum = 0;
    
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

    #pragma omp parallel sections
    {
      #pragma omp section
      {
        for(int i=0; i<n/8; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=n/8; i<2*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=2*n/8; i<3*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=3*n/8; i<4*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=4*n/8; i<5*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=5*n/8; i<6*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=6*n/8; i<7*n/8 ; i++){
          U[i][i] = 1;
        }
      }

      #pragma omp section
      {
        for(int i=7*n/8; i < n ; i++){
          U[i][i] = 1;
        }
      }
    }

    for (int j = 0; j < n; j++){
        
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
        
        #pragma omp sections
        {
           #pragma omp section
           {
            for(int i = j; i < j+((n-j)/8); i++){
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
           #pragma omp section
           {
             for(int i = j+((n-j)/8); i < j+(2*(n-j)/8); i++){
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
           #pragma omp section
           {
             for(int i = j+(2*(n-j)/8); i < j+(3*(n-j)/8); i++){
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
           #pragma omp section
           {
             for(int i = j+(3*(n-j)/8); i < j+(4*(n-j)/8); i++){
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
           #pragma omp section
           {
             for(int i = j+(4*(n-j)/8); i < j+(5*(n-j)/8); i++){
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
           #pragma omp section
           {
             for(int i = j+(5*(n-j)/8); i < j+(6*(n-j)/8); i++){
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
           #pragma omp section
           {
             for(int i = j+(6*(n-j)/8); i < j+(7*(n-j)/8); i++){
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
           #pragma omp section
           {
             for(int i = j+(7*(n-j)/8); i < n; i++){
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
        }
    }
}

