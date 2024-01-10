#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "checkArgs.h"

int checkArgs(int argc) {
    int nUnits = argc - 1;  // Using int instead of double for the number of units
    int root = (int)sqrt(nUnits);  // Using int for the root as well
    int root2 = root * root;
    if (nUnits < 4) {
        printf("INPUT ERROR: Dimension < 2.\n");
        return -1;
    } else if (root2 != nUnits) {
        printf("INPUT ERROR: Dimension of vectors != number of vectors.\n");
        return -1;
    } else {
        return 0;
    }
}
