#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "common.h"
#include "checkArgs.h"
#include "getBasis.h"
#include "listSieve.h"
#include "writeTXT.h"

int main(int argc, char *argv[]) {
    // Seed the random number generator with the current time
    srand(time(NULL));
    // Declare variables
    double** basis;
    double mu;
    double* shortestBasis;
    double* shortestVector;
    // Check command line arguments
    int argStatus = checkArgs(argc);
    if (argStatus == 0) {
        // Read basis vectors from command line arguments
        basis = getBasis(argc, argv);
    } else {
        printf("Error reading inputs.\n");
        return -1;
    }
    // Find the shortest basis vector and calculate mu
    shortestBasis = basis[0];
    for (int i = 0; i < dim; i++) {
        if (L2_norm(basis[i]) < L2_norm(shortestBasis)) {
            shortestBasis = basis[i];
        }
    }
    mu = L2_norm(shortestBasis);
    // Allocate memory for the shortest vector
    shortestVector = (double*)malloc(dim * sizeof(double));
    if (shortestVector == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    // Perform listSieve algorithm to find the shortest vector
    int status = listSieve(basis, mu, shortestVector);
    // Process the results based on the status
    if (status == 0) {
        // A vector shorter than mu is found
        double len = L2_norm(shortestVector);
        printf("Length: %lf\n", len);
        printf("Shortest Vector:\n");
        for (int i = 0; i < dim; i++) {
            printf("%lf ", shortestVector[i]);
        }
        printf("\n");
        // Free allocated memory
        free(shortestVector);
        shortestVector = NULL;
    } else if (status == 1) {
        // No vector found with length less than mu
        printf("No vector found with length less than: %lf.\n Shortest vector has length: %lf\n", mu, mu);
        printf("Length: %lf\n", mu);
        printf("Shortest Vector:\n");
        for (int i = 0; i < dim; i++) {
            printf("%lf ", shortestBasis[i]);
        }
        printf("\n");
        // Free allocated memory
        shortestBasis = NULL;
    } else if (status == -1) {
        // Error in listSieve
        printf("Error in listSieve()\n");
    }
    // Free memory allocated for basis vectors
    for (int i = 0; i < dim; i++) {
        free(basis[i]);
        basis[i] = NULL;
    }
    free(basis);
    basis = NULL;
    return 0;
}