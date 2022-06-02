#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    unsigned int height;
    unsigned int width;
    float **values;
} Matrix;

Matrix *matzero(unsigned int height, unsigned int width);
Matrix *matrand(unsigned int height, unsigned int width);
Matrix *fromarray(float values[], unsigned int height, unsigned int width);
void matfree(Matrix *m);
Matrix *matadd(Matrix *a, Matrix *b);
Matrix *matsub(Matrix *a, Matrix *b);
Matrix *matmul(Matrix *a, Matrix *b);
Matrix *matmulwise(Matrix *a, Matrix *b);
Matrix *matscale(Matrix *m, float scalar);
void matcopy(Matrix *m, Matrix *n);
Matrix *matmap(Matrix *m, float (*func)(float));
Matrix *transpose(Matrix *m);
void matprint(Matrix *m);

#endif // MATRIX_H

