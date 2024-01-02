#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "common.h"
#include "sample.h" 

int sample(float** basis, float radius, float** e_p) {

    for (int i = 0; i < dim; i++) {
        e_p[0][i] = radius * (2 * ((float)rand() / RAND_MAX) - 1);
    }

    for (int i = 0; i < dim; i++) {
        e_p[1][i] = 0;
        for (int j = 0; j < dim; j++) {
            e_p[1][i] += e_p[0][j] * basis[j][i];
        }
        e_p[1][i] = fmod((double)e_p[1][i], 1.0);
    }

    return 0;
}
