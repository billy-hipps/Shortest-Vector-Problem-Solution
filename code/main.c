#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "common.h"
#include "checkArgs.h"
#include "getBasis.h"
#include "listSieve.h"
#include "writeTXT.h"


int main(int argc, char *argv[]) { 

    srand(time(NULL));
    double** basis;
    int argStatus = checkArgs(argc);
    if (argStatus == 0) {
        basis = getBasis(argc, argv);
    } else {
        printf("Error reading inputs.\n");
        return -1;
    }
    
    double mu = 0.685;
    double* shortestVector = (double*)malloc(dim * sizeof(double));
    if (shortestVector == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    int status = listSieve(basis, mu, shortestVector);
    if (status == 0) {
        // The result is available in shortestVecResult
        // write norm to a txt file
        double len = L2_norm(shortestVector);
        printf("len: %lf\n", len);
        printf("SV:\n"); 
        for (int i = 0; i < dim; i++) {
            printf("%lf ", shortestVector[i]);
        }
        printf("\n");
        //writeTXT(len);
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