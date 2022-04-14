#include <stdio.h>
#include <stdlib.h>

#define XDIM 10000
#define YDIM 10000

// We return the pointer
double **alloc_matrix(void) /* Allocate the array */{
    /* Check if allocation succeeded. (check for NULL pointer) */
    int i;
    double **array;
    array = malloc(XDIM*sizeof(double *));

    for(i = 0; i < XDIM; i++)
        array[i] = malloc(YDIM*sizeof(double));
  
    return array;
}

void fill(double** arr){
    int i, j;

    for(i = 0; i < XDIM; i++) 
        for(j = 0; j < YDIM; j++){
            arr[i][j] = (double)(rand()%100); // es posible mejorar modulo y casteo?
        }
}

void compute(double** arr, int kern[3][3]){
    double tmp_sum[2];
    double accum;
    int i, j, x;

    for(i = 0, x = -1; i < XDIM; i++, x++){
        for(j = 0; j < YDIM; j++){
            //printf("processing: %i - %i \n", i, j); 
            if(i >= 1 && j >=1 && i < XDIM-1 && j <YDIM-1){ // no encuentro la forma de eliminar esto 
                tmp_sum[0] = (arr[x][j] + arr[x + 2][j])*kern[0][1];

                tmp_sum[1] = (kern[1][0] + kern[1][1] + kern[1][2])*arr[x + 1][j];
                            
                accum = 9 + (tmp_sum[0] + tmp_sum[1])*0.001;
            }
            arr[i][j] = accum;
        }
    }
}

void print(double** arr){
    int i, j;

    for(i = 0 ; i < 3 ; i++){
        for(j = 0; j < 5; j++){
            printf("array[%i][%i] = %f\n", i, j, arr[i][j]);
        }
      }
}

int main(void){
    double **arr; //hacer float para mejorar tiempo de operaciones?
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