#include <stdio.h>
#include <stdlib.h>
#include "brain.h"


/* Allocate memory for a brain */
brain *brain_allocate_brain(int network_size, double threshold, int rows, int cols) {
    brain *my_brain;

    /* Initialize the brain */
    my_brain = malloc(1 * sizeof(brain));
    if(my_brain == NULL) {
        printf("\nout of memory: brain_allocate_brain - my_brain\n");
    }

    /* Initialize the retina */
    my_brain->retina = twod_array_allocate_array(rows, cols);

    /* Allocate emory for neural_network_size */
    my_brain->neural_network_size = malloc(1 * sizeof(int));
    if( my_brain->neural_network_size == NULL) {
        printf("\nout of memory: brain_allocate_brain - neural_network_size\n");
    }

    /* Set size of neutral network */
    *my_brain->neural_network_size = network_size;

    /* Initialize the network */
    my_brain->network = neuron_initialize_neural_network(network_size, rows*cols, threshold);

    return my_brain;
}

/* Duplicate the array of the picture to the array of retina */
void brain_duplicate_picture_to_retina(int **picture, brain *my_brain, int rows, int cols) {
    twod_array_copy_array(picture, my_brain->retina, rows, cols);
}

/* Print retina array */
void brain_print_retina(brain *my_brain, int rows, int cols) {
    twod_array_print_array(my_brain->retina, rows, cols);
}

/* Learn the pictures */
void brain_learn(brain *my_brain, picture **pictures, double epsilon, int rows, int cols) {
    int i;

    /* Initially set 10 errors to be sure the weights are adjusted correctly */
    int error = 10;

    while(error != 0) {
        i = 0;
        while(pictures[i] != NULL) {

            /* Duplicate picture to retina of the brain */
            brain_duplicate_picture_to_retina(pictures[i]->draw, my_brain, rows, cols);

            /* Set neurral reader */
            neuron_set_neural_reader(my_brain->network, my_brain->retina, rows, cols);

            /* Calcul potential of neuron decider */
            neuron_calcul_neuron_potential(my_brain->network);

            /* Calcul weight of each neural link */
            neuron_calcul_neural_link_weight(my_brain->network, *pictures[i]->wanted_value, epsilon);

            /* Add or remove error in function of the potential calculated */
            error += *my_brain->network->decider->potential != *pictures[i]->wanted_value ? 1 : -1;

            /* Increment for Loop purpose */
            i++;
        }
    }
};

/* Read a letter and tell what it is */
char brain_read(brain *my_brain, int **picture, int rows, int cols) {

    /* Duplicate picture to retina of the brain */
    brain_duplicate_picture_to_retina(picture, my_brain, rows, cols);

    /* Set neurral reader */
    neuron_set_neural_reader(my_brain->network, my_brain->retina, rows, cols);

    /* Show retina */
    brain_print_retina(my_brain, rows, cols);

    /* Calcul potential of neuron decider */
    neuron_calcul_neuron_potential(my_brain->network);

    if(*my_brain->network->decider->potential == 1) {
        printf("\n\n\t==========>It is the letter A!\n");
        return 'A';
    }
    else {
        printf("\n\n\t==========>It is the letter C!\n");
        return 'C';
    }
}

/* Free memory for a brain */
void brain_free_brain(brain *my_brain, int neural_link_size, int rows) {

    /* Free memory allocation of a neuron network */
    neuron_free_neural_network(my_brain->network, neural_link_size);

    /* Free memory allocation for the neural_network_size*/
    free(my_brain->neural_network_size);

    /* Free memory allocation for the 2D array */
    twod_array_free_array(my_brain->retina, rows);

    /* Free memory allocation of struct brain */
    free(my_brain);

}
