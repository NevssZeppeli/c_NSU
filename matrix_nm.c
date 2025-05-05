#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int cols;
    int rows;
    double* data;
} Matrix;

int index(Matrix* m, int row, int col) {
    return row * m->cols + col;
}



void main() {

}