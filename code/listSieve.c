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
double listSieve(double** basis, double** L, double mu, long nSamples) {
    double delta = 1 - (1 / dim);
    double* vReduced = NULL;
    double* v = (double *)calloc(dim, sizeof(double));
    double lenDiff;
    if (v == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (; nSamples < k; nSamples++)  {
        printf("nSamples: %ld\n", nSamples);
        // Sample a vector and reduce it
        int sStatus = sample(basis, v);
        if (sStatus != 0) {
            printf("Error in sample.\n");
            exit(EXIT_FAILURE);
        }
        printf("sample\n");
        for (int i = 0; i < dim; i++) {
            printf("%lf ", v[i]);
        }
        printf("\n");
        vReduced = reduce(v, L, delta, nSamples);
        printf("reduced\n");
        for (int i = 0; i < dim; i++) {
            printf("%lf ", vReduced[i]);
        }
        printf("\n");
        int repeatFlag = isIn(vReduced, L, nSamples);
        // Check if v is in L
        if (repeatFlag == 0) {
            //printf("no repeat\n");
            // Check if v can be reduced by a vector in L
            for (long j = 0; j < nSamples; j++) {
                vec_diff(v, vReduced, L[j]);
                lenDiff = L2_norm(vReduced); 
                if ((lenDiff < mu) && (lenDiff > 0)) {
                    free(v);
                    v = NULL;
                    //printf("recursing\n");
                    printf("nSamples: %ld\n", nSamples);
                    printf("mu = %lf\n", lenDiff);
                    return listSieve(basis, L, lenDiff, nSamples);
                } else {
                    // If v cannot be reduced, add it to L
                    printf("adding\n");
                    memcpy(L[nSamples], vReduced, dim * sizeof(double));
                    memset(v, 0, dim * sizeof(double));
                    break;
                }
            }
        }
    }
free(v);
v = NULL;
return mu;
}