#include "twod_array.h"

typedef struct picture {
    int** draw;
    int* wanted_value;
} picture;

/* Create a set of picture */
picture **pictures_create_pictures(int rows, int cols);

/* Return the draw with some noise ! */
picture *pictures_make_some_noise(picture *pic, double noise_percentage, int rows, int cols);

/* Free allocation memory of picture */
void pictures_free_picture(picture *pic, int rows);

/* Free allocation memory of pictures */
void pictures_free_pictures(picture **pictures, int rows);