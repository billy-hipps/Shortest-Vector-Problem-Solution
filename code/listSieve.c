#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "common.h"
#include "getVecs.h"
#include "reduce.h"
#include "sample.h"

float* listSieve(float** basis, float mu) {

    float** shortVecs = (float**) malloc(1 * sizeof(float));

    float delta = 1 - (1/dim);
    float epsilon = 0.685;

    long k = pow(2, dim);

    float** L = getVecs(basis);

    for (int i = 0; i < k; i++) {
        float** e_p = sample(basis, (epsilon*delta));
        float* p = reduce(e_p[1], L, delta);
        float* v = vec_diff(p, e_p[0]); 
        // if (v not in short vecs) 
                // if (w in L | ||v-w|| <= mu)
                    // return v-w
                // shortvecs + v
    } 
}

// listSieve(B, mu)
// L = {}
// delta = 1-(1/n)
// i = 0
// epsilon = 0.685 
// K = 2^n
// while i < K 
    // i++
    // sample(B epsilon*delta)
    // listreduce(p, L, delta)
    // v = p - e
    // if v not in L
        // if w in L: ||v-w|| <= mu
            // return v-w 
        // L + v