#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "common.h"

// Function using lattice vectors to reduce a sampled lattice vector p
double* reduce(double* p, double** L, double delta, int32_t nSamples) {
    double len_p = delta * l2Norm(p);
    // Loop through the vectors in L to reduce p
    for (int32_t i = 0; i < nSamples; i++) {
        double* diff = vecDiff(p, L[i]);
        double len = l2Norm(diff);
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
