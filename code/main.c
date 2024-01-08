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
    
    // finding the shortest basis 
    double mu;
    double* shortestBasis;
    shortestBasis = basis[0];
    for (int i = 0; i < dim; i++) {
        if (L2_norm(basis[i]) < L2_norm(shortestBasis)) {
        shortestBasis = basis[i];
        }
    }
    mu = L2_norm(shortestBasis);
    double* shortestVector = (double*)malloc(dim * sizeof(double));
    if (shortestVector == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    printf("mu = %lf\n", mu);
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
    } else if (status == 1) {
        printf("No vector found with length less than: %lf.\n Shortest vector has length: %lf\n", mu, mu);
        printf("len: %lf\n", mu);
        printf("SV:\n"); 
        for (int i = 0; i < dim; i++) {
            printf("%lf ", shortestBasis[i]);
        }
        printf("\n");
        //writeTXT(len);
        shortestBasis = NULL;
    } else if (status == -1) {
        printf("Error in listSieve()");
    }

    for (int i = 0; i < dim; i++) {
        free(basis[i]);
        basis[i] = NULL;
    }
    free(basis);
    basis = NULL;

    return 0;
}