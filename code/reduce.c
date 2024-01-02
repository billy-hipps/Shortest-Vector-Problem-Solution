#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "common.h" 

// make this recursive if needed - using flags 

float* reduce(float* p, float** L, float delta) {

    long len_L = sizeof(L) / sizeof(L[0]);
    float len_p = delta * L2_norm(p); 

    for (int i = 0; i < len_L; i++) { 
        // initialise a list to store the difference between p and v 
        float* diff = vec_diff(p, L[i]); 
        // check that p can be reduced by v  
        float len = L2_norm(diff); 
        if (len <= len_p) {
            // update p with the values from p-v
            for (int j = 0; j < dim; j++) {
                p[i] = diff[i]; 
            }
            // p has been updated, free diff 
            free(diff);
            diff = NULL;  
        } 
        // p has not been updated, free diff 
        free(diff);
        diff = NULL;
    } 
    return p;  
}