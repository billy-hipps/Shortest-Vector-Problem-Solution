extern int dim;

extern int c;

void set_dim(double d);

double get_dim();

void scalar_prod(int a, double* vec, double* result);

void vec_diff(double* dest, double* vec1, double* vec2);

double L2_norm(double* vec);

int isIn(double* vec, double** list, long int nVectors);

double dotProd(double* vec1, double* vec2);

double cosSimilarity(double* vec1, double*vec2);
