#include "common.h"
#include <math.h> 

extern int dim;

void set_dim(double d) {
    dim = d;
}

int get_dim() {
    return dim; 
} 

float scalar_prod(int a, float *vec) {
    float *new_vec;
    new_vec = (float*) malloc(dim * sizeof(float));

    for (int i; i < dim; i++) {
        new_vec[i] = vec[i] * a;
    } 
    return *new_vec;
}

float vec_prod(float *vec1, float *vec2) {
    float *new_vec;
    new_vec = (float*) malloc(dim * sizeof(float));

    for (int i; i < dim; i++) {
        new_vec[i] = (vec1[i] * vec2[i]);
    }
    return *new_vec; 
}

void vec_diff(float *vec1, float *vec2) {
    for (int i; i < dim; i++) {
        vec1[i] - vec2[i];
    }
}

float L2_norm(float *vec) {
    float total = 0;
    for (int i; i < dim; i++) {
        total += vec[i] * vec[i];
    }
    total = sqrtf(total);
    return total;
}