#include "neuron.h"
#include "pictures.h"

typedef struct brain {
    int **retina;
    int *neural_network_size;
    neural_network *network;
} brain;


/* Allocate memory for a brain */
brain *brain_allocate_brain(int network_size, double threshold, int rows, int cols);

/* Duplicate the array of the picture to the array of retina */
void brain_duplicate_picture_to_retina(int **picture, brain *my_brain, int rows, int cols);

/* Print retina array */
void brain_print_retina(brain *my_brain, int rows, int cols);

/* Learn the pictures */
void brain_learn(brain *my_brain, picture **pictures, double epsilon, int rows, int cols);

/* Read a letter and tell what it is */
char brain_read(brain *my_brain, int **picture, int rows, int cols);

/* Free memory for a brain */
void brain_free_brain(brain *my_brain, int neural_link_size, int rows);