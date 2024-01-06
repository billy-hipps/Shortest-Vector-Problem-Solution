#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "common.h" 

// make this recursive if needed - using flags 

float* reduce(float* p, float** L, float delta) {

    long int nVecs = 0;
    while (L[nVecs] != NULL) {
        nVecs++;
    }

    float len_p = delta * L2_norm(p); 

    for (int i = 0; i < nVecs; i++) { 

        float* diff = vec_diff(p, L[i]); 
        float len = L2_norm(diff); 
        if ((len <= len_p) && (len != 0)) {
            memcpy(p, diff, sizeof(float));
            free(diff);
            diff = NULL;  
        } 
        free(diff);
        diff = NULL;
    } 
    return p;  
}