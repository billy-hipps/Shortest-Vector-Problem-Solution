#include <stdlib.h>
#include <stdio.h>

#include "cosScore.h"
#include "common.h"

int cosScore(double** basis) {
    double sum = 0;
    long pairCount = 0;
    double similarity;
    double avgSim;
    // Generate average Cosine Similarity of basis vectors
    for (long i = 0; i < (dim-1); i++) {
        for (long j = (i + 1); j < dim; j++) {
            similarity = cosSimilarity(basis[i], basis[j]);
            sum += similarity;
            pairCount++;
        }
    }
    if (pairCount > 0) {
        avgSim = sum/pairCount;
    } else {
        avgSim = 0;
    }
    // Based on everage Cosine Similarity select an appropriate c
    if (avgSim == 1) {
        return 0;  // Basis vectors are identical
    } else if (avgSim == 0.0) {
        return 1;  // c = 1 for similarity 0 or less
    } else if (avgSim < 0.15) {
        return 2;  // c = 2 for similarity between 0 and 0.15
    } else if (avgSim < 0.3) {
        return 3;  // c = 3 for similarity between 0.15 and 0.3
    } else if (avgSim < 0.45) {
        return 4;  // c = 4 for similarity between 0.3 and 0.45
    } else if (avgSim < 0.6) {
        return 5;  // c = 5 for similarity between 0.45 and 0.6
    } else if (avgSim < 0.75) {
        return 6;  // c = 6 for similarity between 0.6 and 0.75
    } else if (avgSim < 1) {
        return 7;  // c = 7 for similarity between 0.75 and 0.9
    }
}
