#include "deep.h"
#include <stdio.h>

#define DATASIZE 4

int main(void) {
    NeuralNetwork *model = multilayer((unsigned int[]){2, 4, 4, 1}, 4);
    Matrix *data_x[] = {
        fromarray((float[]){0, 0}, 2, 1),
        fromarray((float[]){0, 1}, 2, 1),
        fromarray((float[]){1, 0}, 2, 1),
        fromarray((float[]){1, 1}, 2, 1),
    };
    Matrix *data_y[] = {
        fromarray((float[]){0}, 1, 1),
        fromarray((float[]){1}, 1, 1),
        fromarray((float[]){1}, 1, 1),
        fromarray((float[]){0}, 1, 1),
    };
    printf("Before:\n");
    for (int i=0; i<DATASIZE; i++) {
        Matrix *temp = predict(model, data_x[i]);
        matprint(temp);
        matfree(temp);
    }
    fit(model, data_x, data_y, DATASIZE, 10000);
    printf("After:\n");
    for (int i=0; i<DATASIZE; i++) {
        Matrix *temp = predict(model, data_x[i]);
        matprint(temp);
        matfree(temp);
    }
    for (int i=0; i<DATASIZE; i++) {
        matfree(data_x[i]);
        matfree(data_y[i]);
    }
    netfree(model);
    return 0;
}
