#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "getBasis.h"
#include "checkArgs.h"
#include "common.h"

double** getBasis(int argc, char** argv) {
    // Use argument count to infer dimension
    argc -= 1;
    double d;
    d = sqrt((double)argc);
    setDim(d);
    dim = getDim();
    // Allocate memory for a list of pointers to lists to store basis vetcors
    static double** basis;
    basis = (double**)malloc(dim * sizeof(double*));
    if (basis == NULL) {
        printf("MEMORY ERROR: Failed allocation.\n");
        exit(EXIT_FAILURE);
    }
    // Allocate memory for, and copy command line arguments into basis vectors
    for (long i = 1; i < argc; i += dim) {
        basis[i / dim] = (double *)malloc(dim * sizeof(double));
        if (basis[i / dim] == NULL) {
            printf("MEMORY ERROR: Failed allocation.\n");
            exit(EXIT_FAILURE);
        }
        sscanf(argv[i], "[%lf", &basis[i / dim][0]);
        for (long j = 1; j < dim - 1; j++) {
            sscanf(argv[i + j], "%lf", &basis[i / dim][j]);
        }
        sscanf(argv[i + dim - 1], "%lf", &basis[i / dim][dim - 1]);
    }
    return basis;
}
