#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "common.h"


int main(int argc, char *argv[]) { 

    // use argument count to infer dimension 
    argc -= 1;
    double d = sqrt((double)argc);
    set_dim(d);
    dim = get_dim();

    // allocate memory for a list of pointers to lists where the basis vectors will be stored 
    static float** basis;
    basis = (float**) malloc(dim * sizeof(float));
    if (basis == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // allocate memory for, and copy command line arguments into basis vectors 
    for (int i = 0; i < (argc - 1); i++) {
        if ((i == 0) || ((i % dim) == 0)) {
            basis[i] = (float*) malloc(dim * sizeof(float));
            if (basis[i] == NULL) {
                printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
            }
            fscanf(argv[i], "[%f", &basis[i][0]);
            for (int j = (i+1); j < (i + (dim-2)); j++) {
                fscanf(argv[j], "%f", &basis[i][j]);
            }
            fscanf(argv[i + (dim - 1)], "%f]", &basis[i][dim - 1]);
        }
    }   

    for (int k = 0; k < dim; k++) {
        printf("\n");
        printf("vector %d \n", k);
        for (int e = 0; e < dim; e++) {
            printf(&basis[k][e]);
        }
    }

    // free memory allocated for basis vectors after function calls 
    for (int i = 0; i < dim; i++) {
        free(basis[i]);
        basis[i] = NULL;
    }
    free(basis);
    basis = NULL;

    return 0; 
}