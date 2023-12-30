typedef struct {
    float* vec;
    float len;
} shortVec; 

void free_mem(long int nVecs, shortVec* shortVecs, float** L);

shortVec* listSieve(float** basis, float mu);