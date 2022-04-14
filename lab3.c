#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XDIM 10000
#define YDIM 10000

// We return the pointer
float **alloc_matrix(void) /* Allocate the array */{
    /* Check if allocation succeeded. (check for NULL pointer) */
    int i, j;
    float **array;
    array = malloc(XDIM*sizeof(float *));

    for(i = 0; i < XDIM; i++)
        array[i] = malloc(YDIM*sizeof(float));
        
    for(i=0; i<XDIM; i++)
        for(j=0; j<YDIM; j++)
            memset(&array[j][i], i, sizeof(double));

    return array;
}

void fill(float** arr){
    int i, j;

    for(i = 0; i < XDIM; i++) 
        for(j = 0; j < YDIM; j++){
            arr[i][j] = (float)(rand()%100); // es posible mejorar modulo y casteo?
        }
}

void compute(float** arr, float kern[3][3]){
    float tmp_sum[2];
    float accum;//, dato;
    int i, j, x;

    for(i = 0, x = -1; i < XDIM; i++, x++){
        for(j = 0; j < YDIM; j++){
            //printf("processing: %i - %i \n", i, j); 
            if(i >= 1 && j >=1 && i < XDIM-1 && j <YDIM-1){ // no encuentro la forma de eliminar esto 
               // dato = (arr[x][j] + arr[x + 2][j]);
                tmp_sum[0] = (arr[x][j] + arr[x + 2][j])*kern[0][1];

                //dato = arr[x + 1][j];
                tmp_sum[1] = (kern[1][0] + kern[1][1] + kern[1][2])*arr[x + 1][j];
                            
                accum = 9.0f + (tmp_sum[0] + tmp_sum[1])*0.001f;
            }
            arr[i][j] = accum;
        }
    }
}

void print(float** arr){
    int i, j;

    for(i = 0 ; i < 10; i++){
        for(j = 0; j < 10; j++){
            printf("array[%i][%i] = %f\n", i, j, arr[i][j]);
        }
      }
}

int main(void){
    float **arr; //hacer float para mejorar tiempo de operaciones?
    float kern[3][3] = {{0, -4, 0}, {-4, 20, -4}, {0, -4, 0}};

    arr = alloc_matrix();
    fill(arr);
    compute(arr, kern);
    print(arr);

    for(int i = 0; i < XDIM; i++)
        free(arr[i]);
    free(arr);

    return 0;
}