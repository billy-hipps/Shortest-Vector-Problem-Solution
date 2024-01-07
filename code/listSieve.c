#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "listSieve.h"
#include "common.h"
#include "getVecs.h"
#include "reduce.h"
#include "sample.h"

int listSieve(double** basis, double mu, double* result) {
    // allocate memory for an array storing reduced vectors 
    double **shortVecs = (double **)malloc(1 * sizeof(double *));
    if (shortVecs == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    double* v = NULL;
    long int nVecs;
    // set parameters for sample()
    double delta = 1 - (1 / dim);
    double epsilon = 0.685;
    // set limit to how many sample vectors are produced 
    long k = 2 * (pow(2, dim));
    // allocate memory for L - array of lattice vectors used to by reduce() to reduce sample vectors 
    double **L = (double **) malloc(k * sizeof(double *));
    if (result == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    // update values in L with lattice vectors usinf getVecs()
    int gvStatus = getVecs(basis, L);
    if (gvStatus != 0) {
        printf("Error in getVecs.\n");
    }
    // sampling and reduction loop 
    for (long int i = 0; i < k; i++) {
        v = (double*)calloc(dim, sizeof(double));
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
        nVecs = i + 1; 
        if (i == 0) {
            shortVecs[0] = (double *)malloc(dim * sizeof(double));
            if (shortVecs[0] == NULL) {
                printf("Memory allocation failed.\n");
                free(shortVecs);
                return -1;
            }
            memcpy(shortVecs[0], v, dim * sizeof(double));
        } 
        for (int j = 0; j < nVecs; j++) {
            // for every vector in shortVecs calculate the difference between it and v
            double* diff = vec_diff(shortVecs[j], v);
            double lenDiff = L2_norm(diff);
            // check if v can be reduced by a vector in shortVecs without producing a 0 vector 
            if ((lenDiff < mu) && (lenDiff != 0)) {
                memcpy(result, v, dim * sizeof(double));
                // free any memory 
                free(v);
                v = NULL;
                for (int a = 0; a < nVecs; a++) {
                    free(shortVecs[a]);
                    shortVecs[a] = NULL;
                }
                free(shortVecs); 
                shortVecs = NULL;
                for (int b = 0; b < nVecs; b++) {
                    free(L[b]);
                    L[b] = NULL;
                }
                free(L);
                L = NULL;
                // exit 
                return 0; 
            } 
            if (nVecs <= k) {
                size_t newSize = nVecs + 1;
                double **temp = (double **)realloc(shortVecs, newSize * sizeof(double *));
                if (temp == NULL) {
                    printf("Memory reallocation failed.\n");
                    return -1;
                }
                shortVecs = temp;
                shortVecs[nVecs] = (double *)malloc(dim * sizeof(double));
                if (shortVecs[nVecs] == NULL) {
                    printf("Memory allocation failed.\n");
                    return -1;
                } 
                memcpy(shortVecs[nVecs], v, dim * sizeof(double));
                free(v);
                v = NULL;
                break;
            } 
        }
    }
    // sampling loop has terminated without a vector being found shorter than mu
    // iterate over shortVecs to find the shortest vector 
    double* ptr = shortVecs[0];
    for (int l = 1; l < k; l++) {
        if (L2_norm(shortVecs[l]) < L2_norm(ptr)) {
            memcpy(result, shortVecs[l], dim * sizeof(double));
        } else {
            memcpy(result, shortVecs[l], dim * sizeof(double));
            break;
        }
    }
    // free memory 
    for (int a = 0; a < k; a++) {
        free(shortVecs[a]);
        shortVecs[a] = NULL;
    }
    free(shortVecs); 
    shortVecs = NULL;

    for (int b = 0; b < k; b++) {
        free(L[b]);
        L[b] = NULL;
    }
    free(L);
    L = NULL;
    return 0; 
}