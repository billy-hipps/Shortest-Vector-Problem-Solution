extern int dim;

void set_dim(double d);

double get_dim();

long int checkLen(double** list);

void scalar_prod(int a, double *vec, double *result);

double* vec_diff(double *vec1, double *vec2);

double L2_norm(double *vec);

int isIn(double* vec, double** list);