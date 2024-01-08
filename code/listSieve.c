#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "listSieve.h"
#include "common.h"
#include "reduce.h"
#include "sample.h"

// Function to perform the list sieve algorithm
int listSieve(double** basis, double mu, double* result) {
    // Allocate memory for an array storing vectors to be used by reduce()
    double **L = (double **)malloc(dim * sizeof(double *));
    if (L == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    // Initialize L with basis vectors
    for (int i = 0; i < dim; i++) {
        L[i] = (double *)malloc(dim * sizeof(double));
        if (L[i] == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        memcpy(L[i], basis[i], dim * sizeof(double));
    }
    double delta = 1 - (1 / dim);
    int c = 2;
    long k = (pow(2, (c * dim)));
    long int nSamples = dim;
    double* v = NULL;
    // Sampling and reduction loop
    while (nSamples < k) {
        // Allocate memory for a new vector v
        v = (double *)calloc(dim, sizeof(double));
        if (v == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        // Sample a vector and reduce it
        int sStatus = sample(basis, v);
        if (sStatus != 0) {
            printf("Error in sample.\n");
            return -1;
        }
        v = reduce(v, L, delta);
        // Compare v with existing vectors in L
        for (long int j = 0; j < nSamples; j++) {
            double* diff = vec_diff(L[j], v);
            double lenDiff = L2_norm(diff);
            int repeatFlag = isIn(v, L);
            // Check if v is in L
            if (repeatFlag == 0) {
                // Check if v can be reduced by a vector in L without producing a 0 vector
                if ((lenDiff < mu) && (lenDiff > 0)) {
                    memcpy(result, v, dim * sizeof(double));
                    free(v);
                    v = NULL;
                    for (int a = 0; a < nSamples; a++) {
                        free(L[a]);
                        L[a] = NULL;
                    }
                    free(L);
                    L = NULL;
                    return 0;
                } else {
                    // If v cannot be reduced, add it to L
                    size_t newSize = nSamples + 1;
                    double **temp = (double **)realloc(L, newSize * sizeof(double *));
                    if (temp == NULL) {
                        printf("Memory reallocation failed.\n");
                        return -1;
                    }
                    L = temp;
                    L[nSamples] = (double *)malloc(dim * sizeof(double));
                    if (L[nSamples] == NULL) {
                        printf("Memory allocation failed.\n");
                        return -1;
                    }
                    memcpy(L[nSamples], v, dim * sizeof(double));
                    free(v);
                    v = NULL;
                    nSamples++;
                    break;
                }
            }
        }
        // Free memory for vector v
        free(v);
        v = NULL;
        if (nSamples == k) {
            printf("No Vector shorter than mu found.");
            break;
        }
    }
    // Free memory allocated for vectors in L
    for (int a = 0; a < k; a++) {
        free(L[a]);
        L[a] = NULL;
    }
    free(L);
    L = NULL;
    return 1;
}