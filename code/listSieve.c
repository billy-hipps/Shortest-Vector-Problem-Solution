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
    float **shortVecs = (float **)malloc(1 * sizeof(float *));
    if (shortVecs == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    float* v = NULL;
    long int nVecs;
    // set parameters for sample()
    float delta = 1 - (1 / dim);
    float epsilon = 0.685;

    // set limit to how many sample vectors are produced 
    long k = pow(2, dim);

    // allocate memory for L - array of lattice vectors used to by reduce() to reduce sample vectors 
    float **L = (float **) malloc(k * sizeof(float *));
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
        // allocate memory for an array containing e (peturbation vector) and p (sample vector)
        //float **e_p = (float **)malloc(2 * sizeof(float *));
        //if (e_p == NULL) {
            //printf("Memory allocation failed.\n");
            //return -1;
        //}
        //e_p[0] = (float *)malloc(dim * sizeof(float));
        //if (e_p[0] == NULL) {
            //printf("Memory allocation failed.\n");
            //return -1;
        //}
        //e_p[1] = (float *)malloc(dim * sizeof(float));
        //if (e_p[1] == NULL) {
            //printf("Memory allocation failed.\n");
            //return -1;
        //}
        // update e_p with a random peturbation vector (e) and a vector (p)
        v = (float*)calloc(dim, sizeof(float));
        if (v == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        int sStatus = sample(basis, v);
        if (sStatus != 0) {
            printf("Error in sample.\n");
            return -1;
        }
        printf("v before R: \n");
        for (int i = 0; i < dim; i++) {
            printf("%f ", v[i]);
        }
        printf("\n");

        // reduce p 
        v = reduce(v, L, delta);
        printf("v after R: \n");
        for (int i = 0; i < dim; i++) {
            printf("%f ", v[i]);
        }
        printf("\n");
        // subtract e from p to obtain v - a lattice vector 
        //v = vec_diff(p, e_p[0]); 

        // free e_p
        //for (int c = 0; c < 2; c++) {
            //free(e_p[c]);
            //e_p[c] = NULL;
        //}
        //free(e_p);
        //e_p = NULL;

        nVecs = i + 1; 
        if (i == 0) {
            shortVecs[0] = (float *)malloc(dim * sizeof(float));
            if (shortVecs[0] == NULL) {
                printf("Memory allocation failed.\n");
                free(shortVecs);
                return -1;
            }
            memcpy(shortVecs[0], v, dim * sizeof(float));
        } 

        for (int j = 0; j < nVecs; j++) {
            // for every vector in shortVecs calculate the difference between it and v
            float* diff = vec_diff(shortVecs[j], v);
            float lenDiff = L2_norm(diff);
            // check if v can be reduced by a vector in shortVecs without producing a 0 vector 
            if ((lenDiff < mu) && (lenDiff != 0)) {
                memcpy(result, v, dim * sizeof(float));
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
                printf("early exit\n");
                printf("SV: \n");
                for (int i = 0; i < dim; i++) {
                    printf("%f ", result[i]);
                }
                printf("\n");
                return 0; 
            } 
            if (nVecs <= k) {
                size_t newSize = nVecs + 1;
                float **temp = (float **)realloc(shortVecs, newSize * sizeof(float *));
                if (temp == NULL) {
                    printf("Memory reallocation failed.\n");
                    return -1;
                }
                shortVecs = temp;
                shortVecs[nVecs] = (float *)malloc(dim * sizeof(float));
                if (shortVecs[nVecs] == NULL) {
                    printf("Memory allocation failed.\n");
                    return -1;
                } 
                
                memcpy(shortVecs[nVecs], v, dim * sizeof(float));
                free(v);
                v = NULL;
                break;
            } 
        }
    }
    // sampling loop has terminated without a vector being found shorter than mu
    // iterate over shortVecs to find the shortest vector 
    float* ptr = shortVecs[0];
    for (int l = 1; l < k; l++) {
        if (L2_norm(shortVecs[l]) < L2_norm(ptr)) {
            memcpy(result, shortVecs[l], dim * sizeof(float));
        } else {
            memcpy(result, shortVecs[l], dim * sizeof(float));
            break;
        }
    }
    printf("SV: \n");
            for (int i = 0; i < dim; i++) {
                printf("%f ", result[i]);
            }
            printf("\n");

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