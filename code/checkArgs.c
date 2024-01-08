#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "checkArgs.h"

// Function to check if the number of arguments is square and bigger than 4
int checkArgs(int argc) {
    int nUnits = argc - 1;
    double root = sqrt((double)nUnits);
    if (((root*root) == nUnits) && (nUnits >= 4)) {
        return 0;
    } else {
        printf("Error reading inputs.\n");
        return -1;
    }
}