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
    int i;//, j, k; 
    double **array;
    array = malloc(XDIM*sizeof(double *));

    for(i = 0; i < XDIM; i++)
        array[i] = malloc(YDIM*sizeof(double));
  
    return array;
}

void fill(double** arr){
    int i, j;

    for(i = 0; i < XDIM; i++)
        for(j = 0; j < YDIM; j++)
            arr[i][j] = (double)(rand() % 100);
}

void compute(double** arr, int kern[3][3]){
    double tmp_sum[9];
    double dato, accum;
    int i, j;

    for(i = 0; i < XDIM; i++){
        int x = i - 1;

        for(j = 0; j < YDIM; j++){
            //printf("processing: %i - %i \n", i, j); //lo hace muuuuy lento
            if(i >= 1 && j >=1 && i < XDIM-1 && j <YDIM-1){
                dato = arr[x][j];
                tmp_sum[1] = (kern[0][1]*dato)/1000;

                dato = arr[x + 1][j];
                tmp_sum[3] = (kern[1][0]*dato)/1000;
                tmp_sum[4] = (kern[1][1]*dato)/1000;
                tmp_sum[5] = (kern[1][2]*dato)/1000;
                            
                dato = arr[x + 2][j];
                tmp_sum[7] = (kern[2][1]*dato)/1000;

                accum = 9;
                
                double tmp = tmp_sum[1] + tmp_sum[3] + tmp_sum[4] + tmp_sum[5] + tmp_sum[7];
                accum = accum + tmp;
            }
            arr[i][j] = accum;
        }
    }
}

void print(double** arr){
    int i, j;
    for(i = 0 ; i < 3 ; i++)
        for(j = 0 ; j < 5; j++)
            printf("array[%i][%i] = %f\n", i, j, arr[i][j]);
            //printf("array[%i][%i] = %f\narray[%i][%i] = %f\narray[%i][%i] = %f\narray[%i][%i] = %f\narray[%i][%i] = %f\n", i, 0, arr[i][0], i, 1, arr[i][1], i, 2, arr[i][2], i, 3, arr[i][3], i, 4, arr[i][4]);

}

int main(void){
    double **arr;
    int kern[3][3] = {{0, -4, 0}, {-4, 20, -4}, {0, -4, 0}};

    arr = alloc_matrix();
    fill(arr);
    compute(arr, kern);
    print(arr);

    for(int i = 0; i < XDIM; i++)
        free(arr[i]);
    free(arr);

    return 0;
}