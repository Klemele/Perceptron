#include "twod_array.h"

typedef struct neuron {
    double *threshold;
    int *potential;
} neuron;

typedef struct neural_link {
    int *reader;
    double *weight;
} neural_link;

typedef struct neural_network {
    int *neural_link_size;
    neural_link **links;
    neuron *decider;
} neural_network;


/* Initialize a neural link */
neural_link *neuron_initialize_neural_link(int neural_link_size);

/* Initialize a neuron */
neuron *neuron_initialize_neuron(double threshold);

/* Initialize a neuron network */
neural_network *neuron_initialize_neural_network(int neural_network_size, int neural_link_size, double threshold);

/* Calcul the potential of the neuron decider */
void neuron_calcul_neuron_potential(neural_network *network);

/* Calcul the weight for the neural links */
void neuron_calcul_neural_link_weight(neural_network *network, int wanted_value, double epsilon);

/* Set reader neurone in each neural link with the element in the retina */
void neuron_set_neural_reader(neural_network *network, int** retina, int rows, int cols);

/* Free memory allocation of a neural_link */
void neuron_free_neural_link(neural_link *link);

/* Free memory allocation of a neuron */
void neuron_free_neuron(neuron *decider);

/* Free memory allocation of a neuron network */
void neuron_free_neural_network(neural_network *network, int neural_link_size);