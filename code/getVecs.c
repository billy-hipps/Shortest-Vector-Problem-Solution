#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
#include <time.h>

#include "getVecs.h"
#include "common.h"

#define max 5
#define min -5

// function to produce random linear combinations of basis vectors 
// returns L - list of lattice vectors 

float** getVecs(float** basis) {
    
    // set the number of vectors to be sampled 
    long n = pow(2, dim); 

    float** L = (float**) malloc(n * sizeof(float));
    for (int i = 0; i < n; i++) {
        L[i] = (float*) calloc(dim, sizeof(float)); 
        // create 'dim' random numbers 
        int* multipliers = (int*) malloc(dim * sizeof(int));
        for (int j = 0; j < dim; j++) {
            multipliers[i] = (rand() %(max +1 -min)) + min;  
        }
        // assign the linear product of the basis with the random numbers to L[i] 
        for (int k = 0; k < dim; k++) {
            for (int f = 0; f < dim; f++) {
                L[i][k] += basis[f][k] * (float)multipliers[f];
            }
        }
        free(multipliers);
        multipliers = NULL;
    }
    return L; 
}