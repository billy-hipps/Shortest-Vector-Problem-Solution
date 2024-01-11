#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "checkArgs.h"

// Checks if the number of arguments is valid
int checkArgs(int argc) {
    long nUnits = (long)argc - 1;
    long root = (long)sqrt(nUnits);
    long root2 = root * root;
    // Dimension must be > 2
    if (nUnits < 4) {
        printf("INPUT ERROR: Dimension < 2.\n");
        return -1;
    // Basis must be a square matrix
    } else if (root2 != nUnits) {
        printf("INPUT ERROR: Dimension of vectors != number of vectors.\n");
        return -1;
    } else {
        return 0;
    }
}
