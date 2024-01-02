#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "listSieve.h"
#include "common.h"
#include "getVecs.h"
#include "reduce.h"
#include "sample.h"

void free_mem(long int nVecs, shortVec* shortVecs, float** L) {
    for (int a = 0; a < nVecs; a++) {
        free(shortVecs[a].vec);
        shortVecs[a].vec = NULL;
    }
    free(shortVecs); 

    for (int b = 0; b < nVecs; b++) {
        free(L[b]);
        L[b] = NULL;
    }
    free(L);
}

int listSieve(float** basis, float mu, shortVec* result) {
    printf("listSieve");
    shortVec* shortestVec;

    shortVec* shortVecs = (shortVec*)malloc(1 * sizeof(shortVec));
    if (shortVecs == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    float delta = 1 - (1 / dim);
    float epsilon = 0.685;

    long k = pow(2, dim);

    float** L = getVecs(basis);

    for (int i = 0; i < k; i++) {
        float** e_p = sample(basis, (epsilon * delta));
        float* p = reduce(e_p[1], L, delta);
        float* v = vec_diff(p, e_p[0]); 

        shortVec V;
        V.vec = v;
        V.len = L2_norm(v); 

        for (int c = 0; c < 2; c++) {
            free(e_p[c]);
            e_p[c] = NULL;
        }

        if (i == 0) {
            shortVecs[0] = V; 
        } 

        long int nVecs = i + 1;
        for (int j = 0; j < nVecs; j++) {
            float* diff = vec_diff(shortVecs[j].vec, V.vec);
            float lenDiff = L2_norm(diff);
            if ((lenDiff < mu) && (lenDiff != 0)) {
                shortVec* shortestVector = (shortVec*)malloc(sizeof(shortVec));
                if (shortestVector == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
                shortestVector->vec = diff;
                shortestVector->len = lenDiff;

                memcpy(result, shortestVector, sizeof(shortVec));
                free_mem(nVecs, shortVecs, L);
                return 0; 
            }
        }
        size_t newSize = nVecs + 1;
        shortVec* temp = (shortVec*)realloc(shortVecs, newSize * sizeof(shortVec));
        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
        shortVecs = temp;
        shortVecs[nVecs - 1] = V; 
    } 

    long int nVecs = k;

    shortestVec = &shortVecs[0];
    for (int l = 1; l < nVecs; l++) {
        if (shortVecs[l].len < shortestVec->len) {
            memcpy(result, &shortVecs[l], sizeof(shortVec));
            break;
        }
    }

    free_mem(nVecs, shortVecs, L);
    return 0; 
}