#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "brain.h"


int main() {
    int i, j;

    /* Init global const */
    int rows = 5;
    int cols = 4;
    double threshold = 0.5;
    double epsilon = 0.01;

    /* ==================> GENERATE FILE <================== */
    time_t now = time(NULL);
    struct tm *time = localtime(&now);
    char filename[255];
    strftime(filename, 255, "stats_Perceptron_%Y%m%d.csv", time);

    /* Add the path */
    char filepath[] = "%s";
    char filepath_computed[sizeof(filepath) + sizeof(filename)];
    sprintf(filepath_computed, filepath, filename);

    printf(filepath_computed);

    /* Remove stats.csv */
    remove(filepath_computed);

    /* Create file with header */
    FILE *file = fopen(filepath_computed, "a+");
    fprintf(file, "Noise;Real letter;Letter found;");
    fclose(file);

    for (j = 0; j <= 10; j++) {
        /* ==================> CREATE PICTURES <================== */
        picture **pictures = pictures_create_pictures(rows, cols);


        /* ==================> CREATE BRAIN <================== */
        /* Define number of neural network */
        int network_size = 1;
        brain *my_brain = brain_allocate_brain(network_size, threshold, rows, cols);


        /* ==================> LEARNING <================== */
        /* Send picture to the brain for processing */
        brain_learn(my_brain, pictures, epsilon, rows, cols);


        /* ==================> TESTING WITH NOISE <================== */
        printf("\n\n\t ====> Testing letter A with noise <====");
        for (i = 0; i <= 100; i += 5) {
            printf("\n\t ====> Noise = %d %", i);
            picture *pic_a_noised = pictures_make_some_noise(pictures[0], i, rows, cols);
            char letter = brain_read(my_brain, pic_a_noised->draw, rows, cols);

            /* Write to stats.csv : complexity - i; time - seconds; steps - g */
            FILE *file = fopen(filepath_computed, "a+");
            fprintf(file, "\n%d;%c;%c", i, 'A', letter);
            fclose(file);

            /* Free allocation memory of a picture */
            pictures_free_picture(pic_a_noised, rows);
        }

        printf("\n\n\t ====> Testing letter C with noise <====");
        for (i = 0; i <= 100; i += 5) {
            printf("\n\t ====> Noise = %d %", i);
            picture *pic_c_noised = pictures_make_some_noise(pictures[1], i, rows, cols);
            char letter = brain_read(my_brain, pic_c_noised->draw, rows, cols);

            /* Write to stats.csv : complexity - i; time - seconds; steps - g */
            FILE *file = fopen(filepath_computed, "a+");
            fprintf(file, "\n%d;%c;%c", i, 'C', letter);
            fclose(file);

            /* Free allocation memory of a picture */
            pictures_free_picture(pic_c_noised, rows);
        }

        /* Free allocation memory of pictures */
        pictures_free_pictures(pictures, rows);
        /* Free memory for a brain */
        brain_free_brain(my_brain, rows * cols, rows);
    }

    /* Wait user to close */
    printf("\nPress any key to end...\n");
    fflush ( stdout );
    getchar();

    return 0;
}