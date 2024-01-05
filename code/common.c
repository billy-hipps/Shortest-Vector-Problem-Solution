#include <stdlib.h>
#include <stdio.h>
#include <math.h> 

#include "common.h"

int dim;

void set_dim(double d) {
    dim = d;
}

double get_dim() {
    return dim; 
} 

void scalar_prod(int a, float* vec, float* result) {
    for (int i; i < dim; i++) {
        result[i] = vec[i] * a;
    } 
}

float* vec_diff(float* vec1, float* vec2) {
    float* result = (float*) malloc(dim * sizeof(float));
    for (int i; i < dim; i++) {
        result[i] = vec1[i] - vec2[i];
    }
    return result; 
}

float L2_norm(float* vec) {
    float total = 0;
    for (int i = 0; i < dim; i++) {
        total += pow(fabs(vec[i]), 2);
    }
    total = sqrtf(total);
    return total;
}