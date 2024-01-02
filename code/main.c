#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "common.h"
#include "getBasis.h"
#include "listSieve.h"
#include "writeTXT.h"


int main(int argc, char *argv[]) { 

    printf("main");
    float** basis = getBasis(argc, argv);
    float mu = 0.685;
    shortVec shortestVecResult;
    int status = listSieve(basis, mu, &shortestVecResult);
    if (status == 0) {
        // The result is available in shortestVecResult
        // Use the result as needed
        printf("Shortest vector length: %f\n", shortestVecResult.len);

        // write norm to a txt file
        writeTXT(shortestVecResult.len);
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