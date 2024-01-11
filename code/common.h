extern long dim;

extern int c;

void setDim(double d);

double getDim();

double* vecDiff(double *vec1, double *vec2);

double l2Norm(double *vec);

int isIn(double* vec, double** list, long nVectors);

double dotProd(double* vec1, double* vec2);

double cosSimilarity(double* vec1, double*vec2);
