#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "common.h"
#include "sample.h"

#define max 3
#define min -3

// Function to generate a random vector v using the basis vectors
int sample(double** basis, double* v) {
    // Find the longest basis vector
    double longestBasis = L2_norm(basis[0]);
    for (int i = 1; i < dim; i++) {
        if (L2_norm(basis[i]) > longestBasis) {
            longestBasis = L2_norm(basis[i]);
        }
    }
    // Allocate memory for multipliers array
    int* multipliers = (int*) malloc(dim * sizeof(int));
    if (multipliers == NULL) {
        printf("MEMORY ERROR: Error allocating memory.\n");
        return -1;
    }
    // Loop until a valid vector is generated
    while (1) {
        // Initialize vector v to zeros
        for (int i = 0; i < dim; i++) {
            v[i] = 0;
        }
        // Generate 'dim' random numbers as multipliers
        for (int j = 0; j < dim; j++) {
            multipliers[j] = (rand() %(max + 1 - min)) + min;
        }
        // Compute the linear combination of basis vectors with multipliers
        for (int k = 0; k < dim; k++) {
            for (int f = 0; f < dim; f++) {
                v[k] += basis[f][k] * (double)multipliers[f];
            }
        }
        // Check the while condition
        if ((L2_norm(v) > 0) && (L2_norm(v) <= (longestBasis * 2))) {
            break;  // Exit the loop if the condition is met
        }
    }
    // Free memory for multipliers array
    free(multipliers);
    multipliers = NULL;
    return 0;
}
