#include "twod_array.h"
#include <stdio.h>
#include <stdlib.h>

/* Allocate memory to a 2D array */
int **twod_array_allocate_array(int rmax, int cmax) {
    int i =0;

    int** src_arr;
    /* Initialize memory for the pointer of pointer */
    src_arr = malloc(rmax * sizeof(int *));
    if(src_arr == NULL) {
        printf("\nout of memory: twod_array_allocate_array - src_arr\n");
    }

    for(i = 0; i < rmax; i++) {
        /* Allocate memory for each pointer */
        src_arr[i] = malloc(cmax * sizeof(int));
        if(src_arr[i] == NULL) {
            printf("\nout of memory: twod_array_allocate_array - src_arr[i]\n");
        }
    }

    return src_arr;
}

/* Print a 2D array*/
void twod_array_print_array(int **src_arr, int rmax, int cmax) {
    printf("\n\tarray : \n\t");
    int r, c, k;
    k=0;
    for (r = 0; r < rmax; r++) {
        for (c = 0; c < cmax; c++) {
            if (k != r) {
                k=r;
                printf("\n\t\t%d", src_arr[r][c]);
            }
            else {
                printf("\t%d", src_arr[r][c]);
            }
        }
    }
}

/* Copy the source array to the dest array */
void twod_array_copy_array(int **src_arr, int **dest_arr, int rmax, int cmax) {
    int r, c;
    for (r = 0; r < rmax; r++) {
        for (c = 0; c < cmax; c++) {
            dest_arr[r][c] = src_arr[r][c];
        }
    }
}


/* Free memory for a 2D array */
void twod_array_free_array(int **src_arr, int rmax) {
    int i =0;
    for(i = 0; i < rmax; i++) {
        free(src_arr[i]);
    }

    free(src_arr);
}
