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
            memset(&array[j][i], i, sizeof(float));

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
    float tmp_sum[8];
    int i, j, x, y;

    for(j = 0; j < YDIM; j++)
        arr[0][j] = 0; // arr[0][x] = 0 siempre 

    for(i = 1, x = 0; i < XDIM - 1; i++, x++){
        arr[i][0] = arr[x][YDIM - 1]; //arr[x+1][0] = arr[x][9999] siempre
        for(j = 1, y = 0; j < YDIM - 1; j++, y++){
            tmp_sum[3] = kern[1][0]*arr[x+1][y];

            tmp_sum[1] = kern[0][1]*arr[x][y+1];

            tmp_sum[4] = kern[1][1]*arr[x+1][y+1];

            tmp_sum[7] = kern[2][1]*arr[x+2][y+1];
               
            tmp_sum[5] = kern[1][2]*arr[x+1][y+2];
               
            arr[i][j] = 9 + (tmp_sum[1] + tmp_sum[3] + tmp_sum[4] + tmp_sum[5] + tmp_sum[7])*0.001f;
        }
        arr[i][YDIM - 1] = arr[i][YDIM - 2]; // arr[x][9999] = arr[x][9998]
    }

    for(j = 0; j < YDIM; j++)
        arr[XDIM - 1][j] = arr[XDIM - 2][YDIM - 1]; //arr[9999][x] = arr[9998][9999]
}

void print(float** arr){
    int i, j;

    for(i = 0; i < 100; i++)
        for(j = 0; j < 100; j++)
            printf("array[%d][%d] = %f\n", i, j, arr[i][j]);

    for(i = XDIM - 100; i < XDIM; i++)
        for(j = YDIM - 100; j < YDIM ; j++)
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