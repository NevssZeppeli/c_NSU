#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//структура типа Matrix
typedef struct {
    float data[3][3];
} Matrix; 

//ввод элементов матрицы
void input_matrix(Matrix *matrix) {
    printf("Введите элементы матрицы 3x3:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Элемент [%d][%d]: ", i + 1, j + 1);
            scanf("%f", &matrix->data[i][j]);
        }
    }
}

//вывод матрицы с клавиатуры
void print_matrix(Matrix matrix) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f\t", matrix.data[i][j]);
        }
        printf("\n");
    }
}

//чтение матрицы из файла
void read_matrix(Matrix *matrix, char *filename) {
    FILE *file = fopen(filename, "r");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fscanf(file, "%f", &matrix->data[i][j]);
        }
    }
    fclose(file);
}

//запись в файл
void matrix_to_file(Matrix matrix, char *filename) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fprintf(file, "%f\t", matrix.data[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

//определитель методом треугольников
float det(Matrix m) {
    return  (m.data[0][0] * m.data[1][1] * m.data[2][2]) + 
            (m.data[0][1] * m.data[1][2] * m.data[2][0]) + 
            (m.data[0][2] * m.data[1][0] * m.data[2][1]) -
            (m.data[0][2] * m.data[1][1] * m.data[2][0]) -
            (m.data[0][0] * m.data[1][2] * m.data[2][1]) - 
            (m.data[0][1] * m.data[1][0] * m.data[2][2]);
    
}

//обратная матрица
Matrix invert(Matrix m) {
    Matrix inverted;

    float detM = det(m);
    if (detM == 0) {
        printf("Определитель матрицы равен нулю, обратную найти невозможно.\n");
        exit(-1);
    }

    float invDet = 1.0/detM;

    inverted.data[0][0] = (m.data[1][1] * m.data[2][2] - m.data[1][2] * m.data[2][1]) * invDet;
    inverted.data[0][1] = (m.data[0][2] * m.data[2][1] - m.data[0][1] * m.data[2][2]) * invDet;
    inverted.data[0][2] = (m.data[0][1] * m.data[1][2] - m.data[0][2] * m.data[1][1]) * invDet;
    inverted.data[1][0] = (m.data[1][2] * m.data[2][0] - m.data[1][0] * m.data[2][2]) * invDet;
    inverted.data[1][1] = (m.data[0][0] * m.data[2][2] - m.data[0][2] * m.data[2][0]) * invDet;
    inverted.data[1][2] = (m.data[0][2] * m.data[1][0] - m.data[0][0] * m.data[1][2]) * invDet;
    inverted.data[2][0] = (m.data[1][0] * m.data[2][1] - m.data[1][1] * m.data[2][0]) * invDet;
    inverted.data[2][1] = (m.data[0][1] * m.data[2][0] - m.data[0][0] * m.data[2][1]) * invDet;
    inverted.data[2][2] = (m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0]) * invDet;

    matrix_to_file(inverted, "inverted_matrix.txt");
    return inverted;
}

//сумма матрица
Matrix matrix_sum(Matrix a, Matrix b) {
    Matrix summed;

    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            summed.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }    
    matrix_to_file(summed, "summed_matrix.txt");
    return summed;
}

//произведение матриц
Matrix matrix_multiply(Matrix a, Matrix b) {
    Matrix multiplied;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            multiplied.data[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                multiplied.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    matrix_to_file(multiplied, "multiplied_matrix.txt");
    return multiplied;
}


int main() {
    Matrix matrixA, matrixB;

    int choice;
    printf("Выберите, считать матрицу A с клавиатуры (1) или с файла (2):\n");
    scanf("%d", &choice);
    
    if (choice == 1) {
        input_matrix(&matrixA);
        printf("Вид матрицы A:\n");
        print_matrix(matrixA);
    }
    if (choice == 2) {
        read_matrix(&matrixA, "matrixA.txt");
        printf("Вид матрицы A:\n");
        print_matrix(matrixA);
    }
    else if (choice != 0 && choice != 1) {
        printf("Неправильный ввод.\n");
        exit(-1);
    }

    printf("Выберите, считать матрицу A с клавиатуры (1) или с файла (2):\n");
    scanf("%d", &choice);
    
    if (choice == 1) {
        input_matrix(&matrixB);
        printf("\nВид матрицы B:\n");
        print_matrix(matrixB);
    }
    if (choice == 2) {
        read_matrix(&matrixB, "matrixB.txt");
        printf("\nВид матрицы B:\n");
        print_matrix(matrixB);
    }
    else if (choice != 0 && choice != 1) {
        printf("Неправильный ввод.\n");
        return -1;
    }

    printf("\nОпределитель матрицы A = %f\n", det(matrixA));
    printf("\nОпределитель матрицы B = %f\n", det(matrixB));

    printf("\nОбратная матрица А:\n");
    print_matrix(invert(matrixA));
    printf("\nОбратная матрица B:\n");
    print_matrix(invert(matrixB));

    printf("\nСумма матриц A и B:\n");
    print_matrix(matrix_sum(matrixA, matrixB));

    printf("\nПроизведение матриц A и B:\n");
    print_matrix(matrix_multiply(matrixA, matrixB));

    return 0;
}