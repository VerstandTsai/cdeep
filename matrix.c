#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

enum SizeCheckMode {
    MATADD,
    MATSUB,
    MATMUL,
    MATMULWISE,
    MATCOPY
};

float randf() {
    static bool sranded = 0;
    if (!sranded) {
        srand(time(0));
        sranded = 1;
    }
    return (float)rand() / (float)RAND_MAX;
}

void sizecheck(Matrix *a, Matrix *b, enum SizeCheckMode mode) {
    bool iserror = false;
    if (mode == MATMUL) {
        if (a->width != b->height) {
            iserror = 1;
        }
    } else if (a->height != b->height || a->width != b->width) {
        iserror = 1;
    }
    if (iserror) {
        char opname[40];
        switch (mode) {
            case MATADD:
                strcpy(opname, "addition");
                break;
            case MATSUB:
                strcpy(opname, "subtraction");
                break;
            case MATMULWISE:
                strcpy(opname, "element-wise multiplication");
                break;
            case MATMUL:
                strcpy(opname, "multiplication");
                break;
            case MATCOPY:
                strcpy(opname, "copying");
                break;
        }
        printf("Error: matrix %s: matrix size not match.\n", opname);
        exit(1);
    }
}

Matrix *matzero(unsigned int height, unsigned int width) {
    Matrix *m = malloc(sizeof(Matrix));
    m->height = height;
    m->width = width;
    m->values = malloc(sizeof(float*) * height);
    for (int i=0; i<height; i++) {
        m->values[i] = calloc(sizeof(float), width);
    }
    return m;
}

Matrix *matrand(unsigned int height, unsigned int width) {
    Matrix *m = matzero(height, width);
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            m->values[i][j] = randf();
        }
    }
    return m;
}

Matrix *fromarray(float values[], unsigned int height, unsigned int width) {
    Matrix *m = matzero(height, width);
    int k = 0;
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            m->values[i][j] = values[k];
            k++;
        }
    }
    return m;
}

void matfree(Matrix *m) {
    for (int i=0; i<m->height; i++) {
        free(m->values[i]);
    }
    free(m->values);
    free(m);
}

Matrix *matadd(Matrix *a, Matrix *b) {
    sizecheck(a, b, MATADD);
    Matrix *m = matzero(a->height, a->width);
    for (int i=0; i<m->height; i++) {
        for (int j=0; j<m->width; j++) {
            m->values[i][j] = a->values[i][j] + b->values[i][j];
        }
    }
    return m;
}

Matrix *matsub(Matrix *a, Matrix *b) {
    sizecheck(a, b, MATSUB);
    Matrix *m = matzero(a->height, a->width);
    for (int i=0; i<m->height; i++) {
        for (int j=0; j<m->width; j++) {
            m->values[i][j] = a->values[i][j] - b->values[i][j];
        }
    }
    return m;
}

Matrix *matmul(Matrix *a, Matrix *b) {
    sizecheck(a, b, MATMUL);
    Matrix *m = matzero(a->height, b->width);
    for (int i=0; i<m->height; i++) {
        for (int j=0; j<m->width; j++) {
            for (unsigned int k=0; k<a->width; k++) {
                m->values[i][j] += a->values[i][k] * b->values[k][j];
            }
        }
    }
    return m;
}

Matrix *matmulwise(Matrix *a, Matrix *b) {
    sizecheck(a, b, MATMULWISE);
    Matrix *m = matzero(a->height, a->width);
    for (int i=0; i<m->height; i++) {
        for (int j=0; j<m->width; j++) {
            m->values[i][j] = a->values[i][j] * b->values[i][j];
        }
    }
    return m;
}

Matrix *matscale(Matrix *m, float scalar) {
    Matrix *n = matzero(m->height, m->width);
    for (int i=0; i<n->height; i++) {
        for (int j=0; j<n->width; j++) {
            n->values[i][j] = m->values[i][j] * scalar;
        }
    }
    return n;
}

void matcopy(Matrix *m, Matrix *n) {
    sizecheck(m, n, MATCOPY);
    for (int i=0; i<m->height; i++) {
        for (int j=0; j<m->width; j++) {
            m->values[i][j] = n->values[i][j];
        }
    }
}

Matrix *matmap(Matrix *m, float (*func)(float)) {
    Matrix *n = matzero(m->height, m->width);
    for (int i=0; i<n->height; i++) {
        for (int j=0; j<n->width; j++) {
            n->values[i][j] = func(m->values[i][j]);
        }
    }
    return n;
}

Matrix *transpose(Matrix *m) {
    Matrix *n = matzero(m->width, m->height);
    for (int i=0; i<n->height; i++) {
        for (int j=0; j<n->width; j++) {
            n->values[i][j] = m->values[j][i];
        }
    }
    return n;
}

void matprint(Matrix *m) {
    for (int i=0; i<m->height; i++) {
        for (int j=0; j<m->width; j++) {
            printf("%f ", m->values[i][j]);
        }
        printf("\n");
    }
}

