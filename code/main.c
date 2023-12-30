#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "common.h"
#include "getBasis.h"


int main(int argc, char *argv[]) { 

    float** basis = getBasis(argc, argv);
    //float mu = 0.685;
    //float* shortestVec = listSieve(basis, mu);
    //float norm = L2_norm(shortestVec); 

    // write norm to a txt file 
    //writeTXT(norm);

    // free memory allocated 
    //free(shortestVec);
    //shortestVec = NULL;

    for (int i = 0; i < dim; i++) {
        free(basis[i]);
        basis[i] = NULL;
    }
    free(basis);
    basis = NULL;

    return 0;
}