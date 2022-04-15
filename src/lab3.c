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
    float accum;
    int i, j, x;

    for(j = 0; j < YDIM; j++)
        arr[0][j] = 0; // arr[0][x] = 0 siempre 

    for(i = 1, x = 0; i < XDIM - 1; i++, x++){
        arr[i][0] = arr[x][YDIM - 1]; //arr[x+1][0] = arr[x][9999] siempre
        for(j = 1; j < YDIM - 1; j++){
            //printf("processing: %i - %i \n", i, j); 
            tmp_sum[0] = (arr[x][j] + arr[x + 2][j])*kern[0][1];

            tmp_sum[1] = (kern[1][0] + kern[1][1] + kern[1][2])*arr[x + 1][j];
                            
            accum = 9.0f + (tmp_sum[0] + tmp_sum[1])*0.001f;
            
            arr[i][j] = accum;
        }
        arr[i][YDIM - 1] = arr[i][YDIM - 2]; // arr[x][9999] = arr[x][9998]
    }

    for(j = 0; j < YDIM; j++)
        arr[XDIM - 1][j] = arr[XDIM - 2][YDIM - 1]; //arr[9999][x] = arr[9998][9999]
}

void print(float** arr){
    int i, j;

    for(i = 0 ; i < 100 ; i++)
        for(j = 0 ; j < 100 ; j++)
            printf("array[%d][%d] = %f\n", i, j, arr[i][j]);
    for(i = XDIM - 100 ; i < XDIM ; i++)
        for(j = YDIM - 100 ; j < YDIM  ; j++)
            printf("array[%d][%d] = %f\n", i, j, arr[i][j]);
}

int main(void){
    float **arr; 
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