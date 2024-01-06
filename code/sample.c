#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "common.h"
#include "sample.h" 

#define max 2
#define min -2


int sample(float** basis, float* v) {


    float longestBasis = L2_norm(basis[0]);
    for (int i = 1; i < dim; i++) {
        if (L2_norm(basis[i]) > longestBasis) {
            longestBasis = L2_norm(basis[i]);
        }
    }  

    do {
        for (int i = 0; i < dim; i++) {
            v[i] = 0;
        }
        // create 'dim' random numbers 
        int* multipliers = (int*) malloc(dim * sizeof(int));
        if (multipliers == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        
        for (int j = 0; j < dim; j++) {
            multipliers[j] = (rand() %(max +1 -min)) + min;
        }
        // assign the linear product of the basis with the random numbers to L[i] 
        for (int k = 0; k < dim; k++) {
            for (int f = 0; f < dim; f++) {
                v[k] += basis[f][k] * (float)multipliers[f];
            }
        }
        free(multipliers);
        multipliers = NULL;

    } while ((L2_norm(v) < (longestBasis - 0.2)) || (L2_norm(v) > (longestBasis + 0.2)));
    return 0;
}
