#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "writeTXT.h"

void writeTXT(float norm) {
    printf("writeTXT");
    FILE *f = fopen("result.txt", "w");
    if (f == NULL) {
        printf("Error Creating File.");
        exit(1);
    }

    fprintf(f, "%f", norm);

    fclose(f);
}