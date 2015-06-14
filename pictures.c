#include <stdlib.h>
#include <stdio.h>
#include "pictures.h"

/* Initialize a picture */
picture * pictures_initialize_picture(int rows, int cols) {
    /* Alloc memory for each element : picture, draw and wanted_value */
    picture *pic = malloc(1 * sizeof(picture));
    if( pic == NULL) {
        printf("\nout of memory: pictures_initialize_picture - pic\n");
    }
    pic->draw = twod_array_allocate_array(rows, cols);
    pic->wanted_value = malloc(1 * sizeof(int));
    if( pic->wanted_value == NULL) {
        printf("\nout of memory: pictures_initialize_picture - wanted_value\n");
    }

    return pic;
}

/* Create a set of picture */
picture **pictures_create_pictures(int rows, int cols) {
    /* ==================> Init image A <================== */
    /* Allocate memory */
    picture *pic_a = pictures_initialize_picture(rows, cols);
    *pic_a->wanted_value = 1;

    /*Set value */
    /*
     * 1111
     * 1001
     * 1111
     * 1001
     * 1001
     */
    pic_a->draw[0][0] = 1;
    pic_a->draw[0][1] = 1;
    pic_a->draw[0][2] = 1;
    pic_a->draw[0][3] = 1;
    pic_a->draw[1][0] = 1;
    pic_a->draw[1][1] = 0;
    pic_a->draw[1][2] = 0;
    pic_a->draw[1][3] = 1;
    pic_a->draw[2][0] = 1;
    pic_a->draw[2][1] = 1;
    pic_a->draw[2][2] = 1;
    pic_a->draw[2][3] = 1;
    pic_a->draw[3][0] = 1;
    pic_a->draw[3][1] = 0;
    pic_a->draw[3][2] = 0;
    pic_a->draw[3][3] = 1;
    pic_a->draw[4][0] = 1;
    pic_a->draw[4][1] = 0;
    pic_a->draw[4][2] = 0;
    pic_a->draw[4][3] = 1;


    /* ==================> Init image C <================== */
    /* Allocate memory */
    picture *pic_c= pictures_initialize_picture(rows, cols);
    *pic_c->wanted_value = 0;

    /*Set value */
    /*
     * 1111
     * 1000
     * 1000
     * 1000
     * 1111
     */
    pic_c->draw[0][0] = 1;
    pic_c->draw[0][1] = 1;
    pic_c->draw[0][2] = 1;
    pic_c->draw[0][3] = 1;
    pic_c->draw[1][0] = 1;
    pic_c->draw[1][1] = 0;
    pic_c->draw[1][2] = 0;
    pic_c->draw[1][3] = 0;
    pic_c->draw[2][0] = 1;
    pic_c->draw[2][1] = 0;
    pic_c->draw[2][2] = 0;
    pic_c->draw[2][3] = 0;
    pic_c->draw[3][0] = 1;
    pic_c->draw[3][1] = 0;
    pic_c->draw[3][2] = 0;
    pic_c->draw[3][3] = 0;
    pic_c->draw[4][0] = 1;
    pic_c->draw[4][1] = 1;
    pic_c->draw[4][2] = 1;
    pic_c->draw[4][3] = 1;

    /* Allocate memory */
    picture **pictures = malloc(3 * sizeof(picture*));
    if( pictures == NULL) {
        printf("\nout of memory: pictures_create_pictures - pictures\n");
    }
    pictures[0] = pic_a;
    pictures[1] = pic_c;

    /* For loop purpose */
    pictures[2] = NULL;

    return pictures;
}

/* Duplicate a source picture to a dest picture */
void pictures_duplicate_picture(picture *src_pic, picture *dest_pic, int rows, int cols) {
    *dest_pic->wanted_value = *src_pic->wanted_value;
    twod_array_copy_array(src_pic->draw, dest_pic->draw, rows, cols);
}

/* Return the draw with some noise ! */
picture *pictures_make_some_noise(picture *pic, double noise_percentage, int rows, int cols) {
    int counter, i , j, k;
    double number;

    /* Set the loop counter, based on number of element and percentage given */
    number = ((double)rows * (double)cols) * (noise_percentage/100);
    counter  = (int)(number);

    /* Create a new picture, duplicate of the one given */
    picture *new_pic = pictures_initialize_picture(rows, cols);
    pictures_duplicate_picture(pic, new_pic, rows, cols);

    /* Loop on the picture, randomly get a position and setting the value to the invert of the original value */
    i = 0;
    while(i < counter) {
        j = rand() % rows;
        k = rand() % cols;
        if(new_pic->draw[j][k] ==  pic->draw[j][k]) {
            new_pic->draw[j][k] = pic->draw[j][k] == 1 ? 0 : 1;
            i++;
        }
    }

    return new_pic;
}

/* Free allocation memory of picture */
void pictures_free_picture(picture *pic, int rows) {
    /* Free memory allocation for the 2D array */
    twod_array_free_array(pic->draw, rows);

    /* Free memory allocation for the wanted value */
    free(pic->wanted_value);

    /* Free the struct picture */
    free(pic);
}

/* Free allocation memory of pictures */
void pictures_free_pictures(picture **pictures, int rows) {
    int i = 0;
    while(pictures[i] != NULL) {
        /* Free allocation memory of picture */
        pictures_free_picture(pictures[i], rows);

        i++;
    }

    /* Free the struct of pictures */
    free(pictures);
}