#include <stdio.h>
#include <math.h>

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
float matrix_determinant(Matrix m) {
    return  (m.data[0][0] * m.data[1][1] * m.data[2][2]) + 
            (m.data[0][1] * m.data[1][2] * m.data[2][0]) + 
            (m.data[0][2] * m.data[1][0] * m.data[2][1]) -
            (m.data[0][2] * m.data[1][1] * m.data[2][0]) -
            (m.data[0][0] * m.data[1][2] * m.data[2][1]) - 
            (m.data[0][1] * m.data[1][0] * m.data[2][2]);
    
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
        return -1;
    }

    choice = -1;

    printf("Выберите, считать матрицу A с клавиатуры (1) или с файла (2):\n");
    scanf("%d", &choice);
    
    if (choice == 1) {
        input_matrix(&matrixB);
        printf("Вид матрицы B:\n");
        print_matrix(matrixB);
    }
    if (choice == 2) {
        read_matrix(&matrixB, "matrixB.txt");
        printf("Вид матрицы B:\n");
        print_matrix(matrixB);
    }
    else if (choice != 0 && choice != 1) {
        printf("Неправильный ввод.\n");
        return -1;
    }

    printf("Определитель матрицы A = %f\n", matrix_determinant(matrixA));
    printf("Определитель матрицы B = %f\n", matrix_determinant(matrixB));


    return 0;
}