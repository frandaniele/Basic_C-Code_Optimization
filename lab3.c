#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define XDIM 10000
#define YDIM 10000

// We return the pointer
double **alloc_matrix(void) /* Allocate the array */{
    /* Check if allocation succeeded. (check for NULL pointer) */
    int i, j, k; 
    double **array;
    array = malloc(XDIM*sizeof(double *));

    //size_t size_to_alloc = YDIM*sizeof(double); //para calcularlo una sola vez
    for(i = 0; i < XDIM; i++)
        array[i] = malloc(YDIM*sizeof(double));
  
    for(j=0; j<XDIM; j++)
        for(k=0; k<YDIM; k++)
            memset(&array[k][j], j, sizeof(double));
    return array;
}

void fill(double** arr){
    int i, j;
    //time_t t1; 
    //srand ( (unsigned) time (&t1));
    for(i = 0; i < XDIM; i++)
        for(j = 0; j < YDIM; j++)
            arr[i][j] = (double)(rand() % 100);
}

void compute(double** arr, int kern[3][3]){
    double tmp_sum[9];
    double dato, accum;
    int i, j;//, k;//, l;
    for(i = 0; i < XDIM; i++){
        int x = i - 1;
        for(j = 0; j < YDIM; j++){
           // printf("processing: %i - %i \n", i, j); lo hace muuuuy lento
            if(i >= 1 && j >=1 && i < XDIM-1 && j <YDIM-1){
                /*for(k = 0; k < 3; k++){
                   // for(l = 0; l < 3; l++){
                        //int x = i + (l-1);
                        //int y = j + (k-1);// no se usa esta variable,
                       // tmp_sum[l*3+k] = 2*(2*kern[l][k]*dato)/1000 + 1;//capaz un shift en lugar de mult
                        dato = arr[x][j];
                        tmp_sum[k] = 2*(2*kern[0][k]*dato)/1000 + 1;

                        dato = arr[x + 1][j];
                        tmp_sum[3 + k] = 2*(2*kern[1][k]*dato)/1000 + 1;
                        
                        dato = arr[x + 2][j];
                        tmp_sum[6 + k] = 2*(2*kern[2][k]*dato)/1000 + 1;
                   // }
                }*/

                dato = arr[x][j];
                tmp_sum[0] = (4*kern[0][0]*dato)/1000 + 1;
                tmp_sum[1] = (4*kern[0][1]*dato)/1000 + 1;
                tmp_sum[2] = (4*kern[0][2]*dato)/1000 + 1;

                dato = arr[x + 1][j];
                tmp_sum[3] = (4*kern[1][0]*dato)/1000 + 1;
                tmp_sum[4] = (4*kern[1][1]*dato)/1000 + 1;
                tmp_sum[5] = (4*kern[1][2]*dato)/1000 + 1;
                        
                dato = arr[x + 2][j];
                tmp_sum[6] = (4*kern[2][0]*dato)/1000 + 1;
                tmp_sum[7] = (4*kern[2][1]*dato)/1000 + 1;
                tmp_sum[8] = (4*kern[2][2]*dato)/1000 + 1;

                accum = 0;
               /* for(k = 0; k < 3; k++){
                   // for(l = 0; l < 3; l++)
                       // accum = accum + tmp_sum[k*3+l];
                    double tmp = tmp_sum[k*3] + tmp_sum[k*3 + 1] + tmp_sum[k*3 + 2];
                    accum = accum + tmp;
                }*/
                double tmp = tmp_sum[0] + tmp_sum[1] + tmp_sum[2];
                accum = accum + tmp;
                tmp = tmp_sum[3] + tmp_sum[4] + tmp_sum[5];
                accum = accum + tmp;
                tmp = tmp_sum[6] + tmp_sum[7] + tmp_sum[8];
                accum = accum + tmp;
            }
            arr[i][j] = accum;
        }
    }    
}

void print(double** arr){
    int i, j;
    for(i = 0 ; i < 10 ; i++)
        for(j = 0 ; j < 10 ; j++)
            printf("array[%i][%i] = %f\n", i, j, arr[i][j]);
}

int main(void){
   // int i = 0;
    double **arr;
    int kern[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

    arr = alloc_matrix();
    fill(arr);
    compute(arr, kern);
    print(arr);

    for(int i = 0; i < XDIM; i++)
        free(arr[i]);
    free(arr);

    return 0;
}