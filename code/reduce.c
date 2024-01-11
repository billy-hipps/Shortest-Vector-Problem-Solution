#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "common.h"

// recursive function for reducing sample vectors 
double* reduce(double* p, double** L, double delta, long nSamples) {
    double len_p = delta * L2_norm(p);
    // Create a temporary array for the difference outside the loop
    double* diff = (double*)malloc(dim * sizeof(double));
    if (diff == NULL) {
        printf("MEMORY ERROR: Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    // Loop through the vectors in L to reduce p
    for (int i = 0; i < nSamples; i++) {
        vec_diff(diff, p, L[i]);
        double len = L2_norm(diff);
        // Check if lenght is smaller after subtraction
        if ((len <= len_p) && (len != 0)) {
            // Copy new value to p
            memcpy(p, diff, sizeof(double));
            free(diff);
            diff = NULL;
        }
    }

    // Free the temporary array outside the loop
    free(diff);
    diff = NULL;
    return p;
}
