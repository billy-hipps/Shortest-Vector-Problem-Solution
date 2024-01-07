#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "common.h"
#include "sample.h" 

#define max 5
#define min -5


int sample(double** basis, double* v) {

    double longestBasis = L2_norm(basis[0]);
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
                v[k] += basis[f][k] * (double)multipliers[f];
            }
        }
        free(multipliers);
        multipliers = NULL;

    } while ((L2_norm(v) <= (longestBasis * 1.5)) && (L2_norm(v) > (0)));
    return 0;
}
