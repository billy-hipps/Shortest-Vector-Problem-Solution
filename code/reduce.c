#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "common.h"

// Function using lattice vectors to reduce a sampled lattice vector p
double* reduce(double* p, double** L, double delta, long int nSamples) {
    double len_p = delta * L2_norm(p);
    // Loop through the vectors in L to reduce p
    for (int i = 0; i < nSamples; i++) {
        double* diff = vec_diff(p, L[i]);
        double len = L2_norm(diff);
        if ((len <= len_p) && (len != 0)) {
            memcpy(p, diff, sizeof(double));
            free(diff);
            diff = NULL;
        }
        free(diff);
        diff = NULL;
    }
    return p;
}
