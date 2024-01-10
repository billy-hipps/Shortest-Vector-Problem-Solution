#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "listSieve.h"
#include "common.h"
#include "reduce.h"
#include "sample.h"

#define c 7
#define k pow(2, (c*dim))

// Function to perform the list sieve algorithm
double listSieve(double** basis, double** L, double mu, long int nSamples) {
    double delta = 1 - (1 / dim);
    double* vReduced = NULL;
    double* v = (double *)calloc(dim, sizeof(double));
    if (v == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (; nSamples < k; nSamples++) {
        //printf("nSamples: %ld\n", nSamples);
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
                    printf("nSamples: %ld\n", nSamples);
                    printf("mu = %lf\n", lenDiff);
                    return listSieve(basis, L, lenDiff, nSamples);
                } else {
                    // If v cannot be reduced, add it to L
                    memcpy(L[nSamples], vReduced, dim * sizeof(double));
                    memset(v, 0, dim * sizeof(double));
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
        }
    }
    free(v);
    v = NULL;
    return mu;
}