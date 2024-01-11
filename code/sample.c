#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "common.h"
#include "sample.h"

#define max 5
#define min -5

// Function to generate a random vector v using the basis vectors
int sample(double** basis, double* v) {
    // Find the longest basis vector
    double longestBasis = l2Norm(basis[0]);
    for (long i = 1; i < dim; i++) {
        if (l2Norm(basis[i]) > longestBasis) {
            longestBasis = l2Norm(basis[i]);
        }
    }
    // Allocate memory for multipliers array
    int* multipliers = (int*) malloc(dim * sizeof(int));
    if (multipliers == NULL) {
        printf("MEMORY ERROR: Failed allocation.\n");
        return -1;
    }
    // Loop until a valid vector is generated
    while (1) {
        // Initialize vector v to zeros
        for (long i = 0; i < dim; i++) {
            v[i] = 0;
        }
        // Generate 'dim' random numbers as multipliers
        for (long j = 0; j < dim; j++) {
            multipliers[j] = (rand() %(max + 1 - min)) + min;
        }
        // Compute the linear combination of basis vectors with multipliers
        for (long k = 0; k < dim; k++) {
            for (long f = 0; f < dim; f++) {
                v[k] += basis[f][k] * (double)multipliers[f];
            }
        }
        // Check the while condition
        if ((l2Norm(v) > 0) && (l2Norm(v) <= (longestBasis * 2))) {
            break;  // Exit the loop if the condition is met
        }
    }
    // Free memory for multipliers array
    free(multipliers);
    multipliers = NULL;
    return 0;
}
