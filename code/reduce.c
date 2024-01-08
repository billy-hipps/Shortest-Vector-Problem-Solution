#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "common.h"

// Function to recursively reduce a vector p using vectors in L and a reduction factor delta
double* reduce(double* p, double** L, double delta) {
    int nVecs = 2 * pow(2, dim);
    double len_p = delta * L2_norm(p);
    // Loop through the vectors in L to reduce p
    for (int i = 0; i < nVecs; i++) {
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