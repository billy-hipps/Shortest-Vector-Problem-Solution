#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "common.h" 

// function ListReduce(p, L, δ) 
// while(∃vi ∈L:|p−vi| ≤ δ|p|)do
//     p ← p − vi 
//     end while
// return p 
// end function

// make this recursive if needed - using flags 

float* ListReduce(float* p, float** L, float delta) {
 
    long len_L = sizeof(L) / sizeof(L[0]);
    float len_p = delta * L2_norm(p); 

    for (int i = 0; i < len_L; i++) { 
        float* diff = vec_diff(p, L[i]);  
        float len = L2_norm(diff); 
        if (len <= len_p) {
            for (int j = 0; j < dim; j++) {
                p[i] = diff[i]; // update p with the values from p-v 
            }
            free(diff);
            diff = NULL; // diff is not needed anymore 
        } 
    } 
    return p;  
}