#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "common.h"
#include "sample.h" 

float** sample(float** basis, float radius) {
    float** result = (float**)malloc(2 * sizeof(float*));
    float* e = (float*)malloc(dim * sizeof(float));
    float* p = (float*)malloc(dim * sizeof(float));

    srand(time(NULL));

    for (int i = 0; i < dim; i++) {
        e[i] = radius * (2 * ((float)rand() / RAND_MAX) - 1);
    }

    for (int i = 0; i < dim; i++) {
        p[i] = 0;
        for (int j = 0; j < dim; j++) {
            p[i] += e[j] * basis[j][i];
        }
        p[i] = fmod((double)p[i], 1.0);
    }

    result[0] = (float*)malloc(dim * sizeof(float));
    result[1] = (float*)malloc(dim * sizeof(float));

    memcpy(result[0], e, dim * sizeof(float));
    memcpy(result[1], p, dim * sizeof(float));

    free(e);
    free(p);

    return result;
}
