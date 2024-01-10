#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "common.h"
#include "checkArgs.h"
#include "getBasis.h"
#include "listSieve.h"
#include "writeTXT.h"

#define c 7
#define k pow(2, (c*dim))

int main(int argc, char *argv[]) {
    // Seed the random number generator with the current time
    srand(time(NULL));
    // Declare variables
    double** basis;
    double mu;
    double* shortestBasis;
    // Check command line arguments
    int argStatus = checkArgs(argc);
    if (argStatus == 0) {
        // Read basis vectors from command line arguments
        basis = getBasis(argc, argv);
    } else {
        printf("Error reading inputs.\n");
        return -1;
    }
    // Allocate memory for reduced lattice vectors 
    double **L = (double **)malloc((k) * sizeof(double *));
    if (L == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    // Initialize L with basis vectors
    for (int i = 0; i < k; i++) {
        L[i] = (double *)malloc(dim * sizeof(double));
        if (L[i] == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        if (i < dim) {
        memcpy(L[i], basis[i], dim * sizeof(double));
        }
    }
    // Find the shortest basis vector and calculate mu
    shortestBasis = basis[0];
    for (int i = 0; i < dim; i++) {
        if (L2_norm(basis[i]) < L2_norm(shortestBasis)) {
            shortestBasis = basis[i];
        }
    }
    mu = L2_norm(shortestBasis);
    // Perform listSieve algorithm to find the shortest vector
    double result = listSieve(basis, L, mu, dim);
    printf("result = %lf\n", result);
    // Free memory allocated for basis vectors
    for (int i = 0; i < dim; i++) {
        free(basis[i]);
        basis[i] = NULL;
    }
    free(basis);
    basis = NULL;
    return 0;
    // Free memory allocated for lattice vectors
    for (int j = 0; j < k; j++) {
        free(L[j]);
        L[j] = NULL;
    }
    free(L);
    L = NULL;

}
