extern int dim;

void set_dim(double d); 

double get_dim();

void scalar_prod(int a, float *vec, float *result);

void vec_prod(float *vec1, float *vec2, float *result);

float* vec_diff(float *vec1, float *vec2);

float L2_norm(float *vec);