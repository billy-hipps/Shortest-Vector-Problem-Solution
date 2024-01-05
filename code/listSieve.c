#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "listSieve.h"
#include "common.h"
#include "getVecs.h"
#include "reduce.h"
#include "sample.h"

int listSieve(float** basis, float mu, float* result) {
    // allocate memory for an array storing reduced vectors 
    float** shortVecs = (float**)malloc(1 * sizeof(float *));
    if (shortVecs == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    // set parameters for sample()
    float delta = 1 - (1 / dim);
    float epsilon = 0.685;

    // set limit to how many sample vectors are produced 
    long k = pow(2, dim);

    // allocate memory for L - array of lattice vectors used to by reduce() to reduce sample vectors 
    float** L = (float**) malloc(k * sizeof(float *));
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
    for (int i = 0; i < k; i++) {
        // allocate memory for an array containing e (peturbation vector) and p (sample vector)
        float** e_p = (float**)malloc(2 * sizeof(float*));
        if (e_p == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        e_p[0] = (float*)malloc(dim * sizeof(float));
        if (e_p[0] == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        e_p[1] = (float*)malloc(dim * sizeof(float));
        if (e_p[1] == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        // update e_p with a random peturbation vector (e) and a vector (p)
        int sStatus = sample(basis, (epsilon * delta), e_p);
        if (sStatus != 0) {
            printf("Error in sample.");
        }
        // reduce p 
        float* p = reduce(e_p[1], L, delta);
        // subtract e from p to obtain v - a lattice vector 
        float* v = vec_diff(p, e_p[0]); 
        // free e_p
        for (int c = 0; c < 2; c++) {
            free(e_p[c]);
            e_p[c] = NULL;
        }
        free(e_p);
        e_p = NULL;

        if (i == 0) {
            shortVecs[0] = v;
        }

        long int nVecs = i + 1; 
        for (int j = 0; j < nVecs; j++) {
            // for every vector in shortVecs calculate the difference between it and v
            float* diff = vec_diff(shortVecs[j], v);
            float lenDiff = L2_norm(diff);
            // check if v can be reduced by a vector in shortVecs without producing a 0 vector 
            if ((lenDiff < mu) && (lenDiff != 0)) {
                // allocate memory to store v - as shortestVector
                result = v;
                // free any memory 
                for (int a = 0; a < nVecs; a++) {
                    free(shortVecs[a]);
                    shortVecs[a] = NULL;
                }
                free(shortVecs); 

                for (int b = 0; b < nVecs; b++) {
                    free(L[b]);
                    L[b] = NULL;
                }
                free(L);
                // exit 
                return 0; 
            }
        }
        size_t newSize = nVecs + 1;
        float* temp = (float*)realloc(shortVecs, newSize * sizeof(float));
        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            return -1;
        }
        shortVecs = &temp;
        shortVecs[nVecs] = v; 
    }
    // sampling loop has terminated without a vector being found shorter than mu
    long int nVecs = k;
    // iterate over shortVecs to find the shortest vector 
    result = shortVecs[0];
    for (int l = 1; l < nVecs; l++) {
        if (L2_norm(shortVecs[l]) < L2_norm(result)) {
            result = shortVecs[l];
        }
    }

    // free memory 
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
    return 0; 

} 