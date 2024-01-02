#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "getBasis.h"
#include "common.h"

float** getBasis(int argc, char** argv) {

    // use argument count to infer dimension
    argc -= 1;
    double d;
    d = sqrt((double)argc);
    set_dim(d);
    dim = get_dim();

    // allocate memory for a list of pointers to lists where the basis vectors will be stored
    static float **basis;
    basis = (float **)malloc(dim * sizeof(float *));
    if (basis == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // allocate memory for, and copy command line arguments into basis vectors
    for (int i = 1; i < argc; i += dim) {
        basis[i / dim] = (float *)malloc(dim * sizeof(float));
        if (basis[i / dim] == NULL) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        sscanf(argv[i], "[%f", &basis[i / dim][0]);
        for (int j = 1; j < dim - 1; j++) {
            sscanf(argv[i + j], "%f", &basis[i / dim][j]);
        }
        sscanf(argv[i + dim - 1], "%f", &basis[i / dim][dim - 1]);
    }

    return basis;
}