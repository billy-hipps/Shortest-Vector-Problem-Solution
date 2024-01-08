#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "listSieve.h"
#include "common.h"
#include "reduce.h"
#include "sample.h"

int listSieve(double** basis, double mu, double* result) {
    // allocate memory for an array storing vectors to be used by reduce() 
    double **L = (double **)malloc(dim * sizeof(double *));
    if (L == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    for (int i = 0; i < dim; i++) {
        L[i] = (double *)malloc(dim * sizeof(double));
        if (L[i] == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        memcpy(L[i], basis[i], dim * sizeof(double));
    }
    double* v = NULL;
    // set parameters for sample()
    double delta = 1 - (1 / dim);
    // set limit to how many sample vectors are produced 
    int c = 2;
    long k = (pow(2, (c*dim)));
    // initialise variables for sampling
    long int nSamples = dim;
    double* diff;
    double lenDiff;
    int repeatFlag;
    // sampling and reduction loop
    while (nSamples < k) { 
        printf("looping (nSamples: %ld, k: %ld)\n", nSamples, k);
        v = (double *)calloc(dim, sizeof(double));
        if (v == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        int sStatus = sample(basis, v);
        if (sStatus != 0) {
            printf("Error in sample.\n");
            return -1;
        }
        // reduce v 
        v = reduce(v, L, delta); 
        printf("V: \n");
        for (int r = 0; r < dim; r++) {
            printf("%lf ", v[r]);
        }
        printf("\n");
        for (long int j = 0; j < nSamples; j++) {
            // for every vector in L calculate the difference between it and v
            diff = vec_diff(L[j], v);
            lenDiff = L2_norm(diff);
            printf("diff = %lf\n", lenDiff);
            repeatFlag = isIn(v, L); 
            if (repeatFlag == 0) {
                // check if v can be reduced by a vector in L without producing a 0 vector 
                if ((lenDiff < mu) && (lenDiff > 0)) {
                    printf("lendiff: %lf\n", lenDiff);
                    memcpy(result, v, dim * sizeof(double));
                    // free any memory 
                    free(v);
                    v = NULL;
                    for (int a = 0; a < nSamples; a++) {
                        free(L[a]);
                        L[a] = NULL;
                    }
                    free(L); 
                    L = NULL;
                    // exit 
                    return 0; 
                } else {
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
        //free v
        free(v);
        v = NULL;
        if (nSamples == k) {
            printf("No Vector shorter than mu found.");
            break;
        }
    }
    // sampling loop terminated -> could not find a vector smaller than mu. 
    // free memory 
    for (int a = 0; a < k; a++) {
        free(L[a]);
        L[a] = NULL;
    }
    free(L); 
    L = NULL;
    return 1; 
}