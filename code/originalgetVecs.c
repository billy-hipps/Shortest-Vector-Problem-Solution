#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
#include <time.h>

#include "getVecs.h"
#include "common.h"

#define max 2
#define min -2

// function to produce random linear combinations of basis vectors 
// returns L - list of lattice vectors 

int getVecs(double** basis, double** L) {

    long n = 2 * (pow(2, dim)); 

    for (int i = 0; i < n; i++) {

        if (i < (dim)) {
            L[i] = (double*) calloc(dim, sizeof(double)); 
            if (L == NULL) {
                printf("Memory allocation failed.\n");
                return -1;
            }
            L[i] = basis[i];
        } else {
            L[i] = (double*) calloc(dim, sizeof(double)); 
            if (L == NULL) {
                printf("Memory allocation failed.\n");
                return -1;
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
                    L[i][k] += basis[f][k] * (double)multipliers[f];
                }
            }
            free(multipliers);
            multipliers = NULL;
            break;
        }
    }
    return 0; 
}