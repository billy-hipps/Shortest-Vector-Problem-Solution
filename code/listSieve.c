#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "listSieve.h"
#include "common.h"
#include "reduce.h"
#include "sample.h"

// Function to perform the list sieve algorithm
double listSieve(double** basis, double** L, double mu, long int nSamples) {
    double delta = 1 - (1 / dim);
    int c = 6;
    long k = (pow(2, (c * dim)));
    double* v;
    double* vReduced = NULL;
    for (; nSamples <= k; nSamples++) {
        v = (double *)calloc(dim, sizeof(double));
        if (v == NULL) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        // Sample a vector and reduce it
        int sStatus = sample(basis, v);
        if (sStatus != 0) {
            printf("Error in sample.\n");
            exit(EXIT_FAILURE);
        }
        vReduced = reduce(v, L, delta, nSamples);
        for (long int j = 0; j < nSamples; j++) {
            double* diff = vec_diff(L[j], vReduced);
            double lenDiff = L2_norm(diff);
            int repeatFlag = isIn(vReduced, L, nSamples);
            // Check if v is in L
            if (repeatFlag == 0) {
                //printf("no repeat\n");
                // Check if v can be reduced by a vector in L
                if ((lenDiff < mu) && (lenDiff > 0)) {
                    free(v);
                    v = NULL;
                    free(diff);
                    diff = NULL;
                    //printf("recursing\n");
                    printf("mu = %lf\n", lenDiff);
                    return listSieve(basis, L, lenDiff, nSamples);
                } else {
                    // If v cannot be reduced, add it to L
                    size_t newSize = nSamples + 1;
                    double **temp = (double **)realloc(L, newSize * sizeof(double *));
                    if (temp == NULL) {
                        printf("Memory reallocation failed.\n");
                        exit(EXIT_FAILURE);
                    }
                    L = temp;
                    L[nSamples] = (double *)malloc(dim * sizeof(double));
                    if (L[nSamples] == NULL) {
                        printf("Memory allocation failed.\n");
                        exit(EXIT_FAILURE);
                    }
                    memcpy(L[nSamples], vReduced, dim * sizeof(double));
                    free(v);
                    v = NULL;
                    free(diff); 
                    diff = NULL;
                    break;
                }
            } else {
                free(diff);
                diff = NULL;
            }
        } 
        if (nSamples == k) {
            free(v);
            v = NULL;
            break;
        } else {
            continue;
        }
    }
    return mu;
}