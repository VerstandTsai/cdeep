#include "deep.h"

#include <stdlib.h>
#include <math.h>

NeuralNetwork *multilayer(unsigned int layersizes[], unsigned int numlayers) {
    NeuralNetwork *model = malloc(sizeof(NeuralNetwork));
    model->numlayers = numlayers;
    int oneless = numlayers-1;
    model->layers = malloc(numlayers * sizeof(Matrix*));
    model->weights = malloc(oneless * sizeof(Matrix*));
    model->biases = malloc(oneless * sizeof(Matrix*));
    for (int i=0; i<oneless; i++) {
        model->layers[i] = matzero(layersizes[i], 1);
        model->weights[i] = matrand(layersizes[i], layersizes[i+1]);
        model->biases[i] = matzero(layersizes[i+1], 1);
    }
    model->layers[oneless] = matzero(layersizes[oneless], 1);
    return model;
}

void netfree(NeuralNetwork *model) {
    for (int i=0; i<model->numlayers-1; i++) {
        matfree(model->layers[i]);
        matfree(model->weights[i]);
        matfree(model->biases[i]);
    }
    matfree(model->layers[model->numlayers-1]);
    free(model->layers);
    free(model->weights);
    free(model->biases);
    free(model);
}

float sigmoid(float x) {
    return 1.0 / (1 + exp(-x));
}

float dsigmoid(float sigmoidx) {
    return sigmoidx / (1 + sigmoidx);
}

void forward(NeuralNetwork *model, Matrix *input) {
    matcopy(model->layers[0], input);
    for (int i=0; i<model->numlayers-1; i++) {
        Matrix *transposed = transpose(model->weights[i]);
        Matrix *weighted = matmul(transposed, model->layers[i]);
        Matrix *biased = matadd(weighted, model->biases[i]);
        Matrix *activated = matmap(biased, sigmoid);
        matcopy(model->layers[i+1], activated);
        matfree(transposed);
        matfree(weighted);
        matfree(biased);
        matfree(activated);
    }
}

void backward(NeuralNetwork *model, Matrix *desired) {
    int indexlast = model->numlayers-2;
    Matrix *derror = matsub(model->layers[indexlast+1], desired);
    for (int i=indexlast; i>=0; i--) {
        Matrix *derived = matmap(model->layers[i+1], dsigmoid);
        Matrix *dbias = matmulwise(derived, derror);
        Matrix *transposed = transpose(dbias);
        Matrix *dweight = matmul(model->layers[i], transposed);
        Matrix *newweight = matsub(model->weights[i], dweight);
        Matrix *newbias = matsub(model->biases[i], dbias);
        matfree(derror);
        derror = matmul(model->weights[i], dbias);
        matcopy(model->weights[i], newweight);
        matcopy(model->biases[i], newbias);
        matfree(derived);
        matfree(dbias);
        matfree(transposed);
        matfree(dweight);
        matfree(newweight);
        matfree(newbias);
    }
    matfree(derror);
}

void fit(NeuralNetwork *model, Matrix *data_x[], Matrix *data_y[], unsigned int datasize, unsigned int epochs) {
    for (int i=0; i<epochs; i++) {
        for (int j=0; j<datasize; j++) {
            forward(model, data_x[j]);
            backward(model, data_y[j]);
        }
    }
}

Matrix *predict(NeuralNetwork *model, Matrix *input) {
    forward(model, input);
    Matrix *layeralias = model->layers[model->numlayers-1];
    Matrix *result = matzero(layeralias->height, layeralias->width);
    matcopy(result, layeralias);
    return result;
}

