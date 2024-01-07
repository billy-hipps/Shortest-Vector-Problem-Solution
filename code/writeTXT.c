#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "writeTXT.h"

void writeTXT(double norm) {
    printf("writeTXT");
    FILE *f = fopen("result.txt", "w");
    if (f == NULL) {
        printf("Error Creating File.");
        exit(1);
    }

    fprintf(f, "%lf", norm);

    fclose(f);
}