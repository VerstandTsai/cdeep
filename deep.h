#ifndef DEEP_H
#define DEEP_H

#include "matrix.h"

typedef struct {
    unsigned int numlayers;
    Matrix **layers;
    Matrix **weights;
    Matrix **biases;
} NeuralNetwork;

NeuralNetwork *multilayer(unsigned int layersizes[], unsigned int numlayers);
void netfree(NeuralNetwork *model);
void fit(NeuralNetwork *model, Matrix *data_x[], Matrix *data_y[], unsigned int datasize, unsigned int epochs);
Matrix *predict(NeuralNetwork *model, Matrix *input);

#endif // DEEP_H

