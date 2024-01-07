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

void scalar_prod(int a, double* vec, double* result) {
    for (int i; i < dim; i++) {
        result[i] = vec[i] * a;
    } 
}

double* vec_diff(double* vec1, double* vec2) {
    double* result = (double*) malloc(dim * sizeof(double));
    for (int i; i < dim; i++) {
        result[i] = vec1[i] - vec2[i];
    }
    return result; 
}

double L2_norm(double* vec) {
    double total = 0;
    for (int i = 0; i < dim; i++) {
        total += pow(fabs(vec[i]), 2);
    }
    total = sqrtf(total);
    return total;
}

int isIn(double* vec, double** list) {
    int nVecs = (sizeof(list)/sizeof(list[0]));
    int flag = 0;
    for (int i = 0; i < nVecs; i++) {
        if (L2_norm(vec) == L2_norm(list[i])) {
            for (int j = 0; j < dim; j++) {
                if (vec[j] == list[i][j]) {
                    flag = 1; 
                    return flag;
                }
            }
        }
    }
    return flag; 
}