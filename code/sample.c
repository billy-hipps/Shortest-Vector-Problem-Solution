#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "common.h"
#include "sample.h" 

float** sample(float** basis, float radius) {
    
    // create a pointer array to store e and p so they can be returned together 
    float** result[2];

    // initialise vectors e, v, and p. 
    float* e = (float*)malloc(dim * sizeof(float));
    float* p = (float*)malloc(dim * sizeof(float));

    // generate random values for e 
    for (int i = 0; i < dim; i++) {
        e[i] = radius * (2 * randomFloat() - 1); // generate a random float between -radius and +radius 
    }

    // find p by doing e mod basis 
    for (int i = 0; i < dim; i++) {
        p[i] = 0;
        for (int j = 0; j < dim; j++) {
            p[i] += e[j] * basis[j][i];
        }
        p[i] = fmod(p[i], 1.0);  // Take e modulo B
        }
    
    result[0] = e;
    result[1] = p; 

    return **result;
}

