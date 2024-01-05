#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "common.h"
#include "getBasis.h"
#include "listSieve.h"
#include "writeTXT.h"


int main(int argc, char *argv[]) { 

    srand(time(NULL));
    float** basis = getBasis(argc, argv);
    float mu = 0.685;
    float* shortestVector = (float*)malloc(dim * sizeof(float));
    if (shortestVector == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    int status = listSieve(basis, mu, shortestVector);
    if (status == 0) {
        // The result is available in shortestVecResult
        // write norm to a txt file
        printf("shortest vector:\n");
        for (int i = 0; i < dim; i++) {
            printf("%f\n", shortestVector[i]);
        }
        float len = L2_norm(shortestVector);
        writeTXT(len);
        free(shortestVector);
        shortestVector = NULL;
    } else {
        printf("Error in listSieve.\n");
    }

    for (int i = 0; i < dim; i++) {
        free(basis[i]);
        basis[i] = NULL;
    }
    free(basis);
    basis = NULL;

    return 0;
}