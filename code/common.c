#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "common.h"

// Global variable to store the dimension
int dim;

// Function to set the global dimension variable
void set_dim(double d) {
    dim = d;
}

// Function to get the global dimension variable
double get_dim() {
    return dim;
}

// Function to check the length of a 2D array (list)
long int checkLen(double** list) {
    // Calculate the length by dividing the total size by the size of one element
    long int len = sizeof(list) / sizeof(list[0]);
    return len;
}

// Function to compute the scalar product of a vector and a scalar
void scalar_prod(int a, double* vec, double* result) {
    for (int i = 0; i < dim; i++) {
        result[i] = vec[i] * a;
    }
}

// Function to compute the element-wise difference of two vectors
double* vec_diff(double* vec1, double* vec2) {
    // Allocate memory for the result vector
    double* result = (double*)malloc(dim * sizeof(double));
    for (int i = 0; i < dim; i++) {
        result[i] = vec1[i] - vec2[i];
    }
    return result;
}

// Function to compute the L2 norm (Euclidean norm) of a vector
double L2_norm(double* vec) {
    double total = 0;
    for (int i = 0; i < dim; i++) {
        total += pow(fabs(vec[i]), 2);
    }
    // Calculate the square root of the sum of squared elements
    total = sqrt(total);
    return total;
}

// Function to check if a vector is in a list of vectors
int isIn(double* vec, double** list) {
    long int len = checkLen(list);
    int flag = 0;
    for (long int i = 0; i < len; i++) {
        for (int j = 0; j < dim; j++) {
            if (vec[j] == list[i][j]) {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}