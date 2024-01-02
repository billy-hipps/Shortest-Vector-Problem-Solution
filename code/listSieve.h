typedef struct {
    float* vec;
    float len;
} shortVec; 

void free_mem(long int nVecs, shortVec* shortVecs, float** L);

int listSieve(float** basis, float mu, shortVec* result);