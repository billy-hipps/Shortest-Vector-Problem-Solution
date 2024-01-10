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
    double* vReduced = NULL;
    double*v = (double *)calloc(dim, sizeof(double));
    if (v == NULL) {
        printf("MEMORY ERROR: Error allocating memory.\n");
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
            //printf("J: %ld\n", j);
            double* diff = vec_diff(L[j], vReduced);
            double lenDiff = L2_norm(diff);
            int repeatFlag = isIn(vReduced, L, nSamples);
            // Check if v is in L
            if (repeatFlag == 0) {
                // Check if v can be reduced by a vector in L
                if ((lenDiff < mu) && (lenDiff > 0)) {
                    free(v);
                    v = NULL;
                    free(diff);
                    diff = NULL;
                    printf("mu = %lf\n", lenDiff);
                    return listSieve(basis, L, lenDiff, nSamples);
                } else {
                    // If v cannot be reduced, add it to L

                    memcpy(L[nSamples], vReduced, dim * sizeof(double));
                    memset(v, 0, dim *sizeof(double));
                }
            } else {
                free(diff);
                diff = NULL;
            }
        } 
    }
    free(v);
    v = NULL;
    return mu;
}
