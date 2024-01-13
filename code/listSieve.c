#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#include "listSieve.h"
#include "common.h"
#include "reduce.h"
#include "sample.h"

#define k pow(2, (c*dim))

// Function to perform the list sieve algorithm
double listSieve(double** basis, double** L, double mu, int32_t nSamples) {
    double delta = 1 - (1 / dim);
    double* vReduced = NULL;
    double* diff;
    double lenDiff;
    double* v = (double*)calloc(dim, sizeof(double));
    if (v == NULL) {
        printf("MEMORY ERROR: Failed allocation.\n");
        exit(EXIT_FAILURE);
    }
    for (; nSamples < k; nSamples++) {
        // Sample a vector and reduce it
        int sStatus = sample(basis, v);
        if (sStatus != 0) {
            printf("Error in sample.\n");
            exit(EXIT_FAILURE);
        }
        vReduced = reduce(v, L, delta, nSamples);
        int repeatFlag = isIn(vReduced, L, nSamples);
        // Check if v is in L
        if (repeatFlag == 0) {
            for (int32_t j = 0; j < nSamples; j++) {
                diff = vecDiff(vReduced, L[j]);
                lenDiff = l2Norm(diff);
                // Check if v can be reduced by a vector in L
                if ((lenDiff < mu) && (lenDiff > 0)) {
                    free(v);
                    v = NULL;
                    free(diff);
                    diff = NULL;
                    // Recurse into lenDiff
                    return listSieve(basis, L, lenDiff, nSamples);
                } else {
                    // If v cannot be reduced, add it to L
                    memcpy(L[nSamples], vReduced, dim * sizeof(double));
                    // Reset v to 0s
                    memset(v, 0, dim * sizeof(double));
                    free(diff);
                    diff = NULL;
                    break;
                }
            }
        }
    }
    // Sampling limit has been reached
    free(v);
    v = NULL;
    // No smaller mu found
    return mu;
}
