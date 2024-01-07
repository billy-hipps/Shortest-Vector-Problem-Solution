#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
#include <time.h>

#include "getVecs.h"
#include "sample.h"
#include "common.h"

// function to produce random linear combinations of basis vectors 
// returns L - list of lattice vectors 

int getVecs(double** basis, double** L) {

    long n = 2 * (pow(2, dim)); 

    for (int i = 0; i < n; i++) {
        L[i] = (double*) calloc(dim, sizeof(double)); 
        if (L == NULL) {
            printf("Memory allocation failed.\n");
            return -1;
        }
        // add do while loop to sample unique vectors 
        sample(basis, L[i]);
    }
    return 0; 
}