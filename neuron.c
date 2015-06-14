#include <stdlib.h>
#include <stdio.h>
#include "neuron.h"


/* Initialize a neural link */
neural_link *neuron_initialize_neural_link(int neural_link_size) {
    /* Allocate memory*/
    neural_link *link;
    link = malloc(1 * sizeof(neural_link));
    if(link == NULL) {
        printf("\nout of memory: neuron_initialize_neural_link - link\n");
    }
    link->reader = malloc(1 * sizeof(int));
    if( link->reader == NULL) {
        printf("\nout of memory: neuron_initialize_neural_link - reader\n");
    }
    link->weight = malloc(1 * sizeof(double));
    if( link->weight == NULL) {
        printf("\nout of memory: neuron_initialize_neural_link - weight\n");
    }

    /* Set init value */
    *link->weight = rand() % (neural_link_size-1) + (-(neural_link_size/2-1));
    *link->reader = -1;

    return link;
}

/* Initialize a neuron */
neuron *neuron_initialize_neuron(double threshold) {
    /* Allocate memory*/
    neuron *decider;
    decider = malloc(1 * sizeof(neuron));
    if(decider == NULL) {
        printf("\nout of memory: neuron_initialize_neuron - decider\n");
    }
    decider->potential = malloc(1 * sizeof(int));
    if(decider->potential == NULL) {
        printf("\nout of memory: neuron_initialize_neuron - potential\n");
    }
    decider->threshold = malloc(1 * sizeof(double));
    if(decider->threshold == NULL) {
        printf("\nout of memory: neuron_initialize_neuron - threshold\n");
    }

    /* Set init value */
    *decider->threshold = threshold;
    *decider->potential = -1;

    return decider;
}

/* Initialize a neuron network */
neural_network *neuron_initialize_neural_network(int neural_network_size, int neural_link_size, double threshold) {
    int i = 0;
    neural_network *network;

    /* Initialize memory for the pointer of neural_network */
    network = malloc(neural_network_size * sizeof(neural_network ));
    if(network == NULL) {
        printf("\nout of memory: neuron_initialize_neural_network - network\n");
    }

    /*  Init of a neuron */
    network->decider = neuron_initialize_neuron(threshold);

    /* Allocate emory for neural_link_size */
    network->neural_link_size = malloc(1 * sizeof(int));
    if(network->neural_link_size == NULL) {
        printf("\nout of memory: neuron_initialize_neural_network - neural_link_size\n");
    }
    /* Set size of neutral link */
    *network->neural_link_size = neural_link_size;

    /* Allocate memory for the neural links */
    network->links = malloc(neural_link_size * sizeof(neural_link *));
    if(network->links == NULL) {
        printf("\nout of memory: neuron_initialize_neural_network - links\n");
    }
    for(i = 0; i < neural_link_size; i++) {
        /* Init of a neural_link */
        network->links[i] = neuron_initialize_neural_link(neural_link_size);
    }

    return network;
}

/* Calcul the potential of the neuron decider */
void neuron_calcul_neuron_potential(neural_network *network) {
    int i;
    double res = 0;

    /* Calcul sum */
    for(i = 0; i < *network->neural_link_size; i++) {
        res += *network->links[i]->weight * *network->links[i]->reader - *network->decider->threshold;
    }

    /* Set value of potential, based on the potential compared to the threshold */
    *network->decider->potential = res > *network->decider->threshold ? 1 : 0;
}

/* Calcul the weight for the neural links */
void neuron_calcul_neural_link_weight(neural_network *network, int wanted_value, double epsilon) {
    int i;

    for(i = 0; i < *network->neural_link_size; i++) {
        *network->links[i]->weight += epsilon  * (wanted_value - *network->decider->potential) * *network->links[i]->reader;
    }
}

/* Set reader neurone in each neural link with the element in the retina */
void neuron_set_neural_reader(neural_network *network, int **retina, int rows, int cols){
    int i, j, counter;
    counter = 0;
    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            *network->links[counter++]->reader = retina[i][j];
        }
    }
}

/* Free memory allocation of a neural_link */
void neuron_free_neural_link(neural_link *link) {
    /* Free memory allocation for the reader */
    free( link->reader);
    /* Free memory allocation for the weight */
    free( link->weight);
    /* Free the struct neural_link */
    free(link);
}

/* Free memory allocation of a neuron */
void neuron_free_neuron(neuron *decider) {
    /* Free memory allocation for the potential */
    free(decider->potential);
    /* Free memory allocation for the threshold */
    free(decider->threshold);
    /* Free memory allocation for the neuron */
    free(decider);
}

/* Free memory allocation of a neuron network */
void neuron_free_neural_network(neural_network *network, int neural_link_size)
{
    int i;

    for(i = neural_link_size-1 ; i >= 0; i--) {
        /* Free memory allocation of a neural_link */
        neuron_free_neural_link(network->links[i]);
    }

    /* Free memory allocation of links */
    free(network->links);

    /* Free memory allocation of neural_link_size */
    free(network->neural_link_size);

    /* Free memory allocation of a neuron */
    neuron_free_neuron(network->decider);

    /* Free the struct neural_network */
    free(network);
}