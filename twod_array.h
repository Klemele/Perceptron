/* Allocate memory to a 2D array */
int **twod_array_allocate_array(int rmax, int cmax);

/* Print a 2D array*/
void twod_array_print_array(int **arr, int r, int c);

/* Copy the source array to the dest array */
void twod_array_copy_array(int **src_arr, int **dest_arr, int rmax, int cmax);

/* Free memory for a 2D array */
void twod_array_free_array(int **src_arr, int rmax);