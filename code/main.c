#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "common.h"
#include "checkArgs.h"
#include "getBasis.h"
#include "listSieve.h"
#include "cosScore.h"

#define k pow(2, (c*dim))

int main(int argc, char *argv[]) {
    // Open a file to store the result
    FILE *f = fopen("result.txt", "w");
    if (f == NULL) {
        printf("FILE ERROR: Could not create 'result.txt'.\n");
        return -1;
    }
    fclose(f);
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
        return -1;
    }
    c = cosScore(basis);
    if (c == 0) {
        printf("INPUT ERROR: Basis vectors are the same.\n");
        return -1;
    }
    // Allocate memory for reduced lattice vectors
    double** L = (double**)malloc((k) * sizeof(double*));
    if (L == NULL) {
        printf("MEMORY ERROR: Failed allocation.\n");
        return -1;
    }
    // Initialize L with basis vectors
    for (long i = 0; i < k; i++) {
        L[i] = (double*)malloc(dim * sizeof(double));
        if (L[i] == NULL) {
            printf("MEMORY ERROR: Failed allocation.\n");
            return -1;
        }
        if (i < dim) {
        memcpy(L[i], basis[i], dim * sizeof(double));
        }
    }
    // Find the shortest basis vector and calculate mu
    shortestBasis = basis[0];
    for (long i = 0; i < dim; i++) {
        if (l2Norm(basis[i]) < l2Norm(shortestBasis)) {
            shortestBasis = basis[i];
        }
    }
    // Start search using length of shortest basis vector
    mu = l2Norm(shortestBasis);
    // Perform listSieve algorithm to find the shortest vector
    double result = listSieve(basis, L, mu, dim);
    // Write the result to result.txt
    FILE *ptr = fopen("result.txt", "w");
    if (f != NULL) {
        fprintf(f, "%lf", result);
        fclose(ptr);
    } else {
        printf("FILE ERROR: Error reopening 'result.txt'.\n");
        return -1;
    }
    // Free memory allocated for basis vectors
    for (long i = 0; i < dim; i++) {
        free(basis[i]);
        basis[i] = NULL;
    }
    free(basis);
    basis = NULL;
    // Free memory allocated for lattice vectors
    for (long j = 0; j < k; j++) {
        free(L[j]);
        L[j] = NULL;
    }
    free(L);
    L = NULL;
    return 0;
}
