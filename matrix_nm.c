#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct matrix{
    int n, m;
    double** data;
};
typedef struct matrix Matrix;

//функция инициализации
Matrix init(int n, int m){
    Matrix res;
    res.n = n;
    res.m = m;
    res.data = (double**)(malloc(sizeof(double*)*n));
    for(int i = 0; i < n; i++)
        res.data[i] = (double*)(malloc(sizeof(double)*m));
    return res;
}

//очистка памяти
void free_matrix(Matrix a){
    for(int i = 0; i < a.n; i++) {
        free(a.data[i]);
    }
    free(a.data);
}

//вывод матрицы
Matrix print_matrix(Matrix a){
    for (int i = 0; i < a.n; i++){
        for (int j = 0; j < a.m; j++){
            printf("%.2f\t", a.data[i][j]);
        }
        printf("\n");
    }
}

//минор, нужно для определителей высоких порядков
Matrix minor(Matrix a, int n, int m){
    Matrix res = init(a.n - 1, a.m - 1);
    for(int i = 0; i < a.n; i++){
        for(int j = 0; j < a.m; j++){
            if ((i != n) && (j != m)) {
                if ((i < n) && (j < m))
                    res.data[i][j] = a.data[i][j];
                if ((i > n) && (j < m))
                    res.data[i-1][j] = a.data[i][j];
                if ((i < n) && (j > m))
                    res.data[i][j - 1] = a.data[i][j];
                if ((i > n) && (j > m))
                    res.data[i-1][j-1] = a.data[i][j];
            }
        }
    }
    return res;
}

//сумма
Matrix sum(Matrix a, Matrix b){
    Matrix res = init(a.n, a.m);
    for (int i = 0; i < a.n; i++){
        for (int j = 0; j < a.m; j++){
            res.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return res;
}

//умножение на скаляр лямбда
Matrix mult_on_scalar(Matrix a, double lambda){
    Matrix res = init(a.n, a.m);
    for (int i = 0; i < a.n; i++){
        for (int j = 0; j < a.m; j++){
            res.data[i][j] = a.data[i][j] * lambda;
        }
    }
    return res;
}

//транспонирование
Matrix transpose(Matrix a){
    Matrix res = init(a.m, a.n); 
    for(int i = 0; i < a.n; i++){
        for(int j = 0; j < a.m; j++){
            res.data[j][i] = a.data[i][j]; 
        }
    }
    return res;
}

//заполнение рандомными числами
void mat_random(Matrix *matrix) {
    for (int i = 0; i < matrix->n; i++) {
        for (int j = 0; j < matrix->m; j++) {
            matrix->data[i][j] = (double)rand() / RAND_MAX * 10.0f; 
        }
    }
}

//чтение с файла
Matrix read_from_file(const char* filename, Matrix a) {
    FILE* file = fopen(filename, "r");
    if(!file) {
        printf("Файл не найден.\n");
        exit(-1);
    }

    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            fscanf(file, "%lf", &a.data[i][j]);
        }
    }

}

//оперделитель
double det(Matrix a) {
    if (a.n != a.m) {
        printf("Определитель можно вычислить только для квадратных матриц.\n");
        exit(-1);
    }

    double deter = 1.0;
    Matrix temp = init(a.n, a.m);

    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            temp.data[i][j] = a.data[i][j];
        }
    }
    for (int i = 0; i < temp.n; i++) {
        double pivot = temp.data[i][i];
        if (fabs(pivot) < 1e-12) {
            free_matrix(temp);
            return 0.0;
        }
        deter *= pivot;
        for (int j = i + 1; j < temp.n; j++) {
            double factor = temp.data[j][i] / pivot;
            for (int k = i; k < temp.m; k++) {
                temp.data[j][k] -= factor * temp.data[i][k];
            }
        }
    }
    free_matrix(temp);
    return deter;
}


//обратная матрица
Matrix invert(Matrix a) {
    if (a.n != a.m) {
        printf("Матрица не квадратная, обратной матрицы не существует.\n");
        exit(-1);
    }

    int n = a.n;
    Matrix augmented = init(n, 2 * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented.data[i][j] = a.data[i][j];
        }
        augmented.data[i][i + n] = 1.0; 
    }

    for (int i = 0; i < n; i++) {
        double pivot = augmented.data[i][i];
        if (fabs(pivot) < 1e-6) {
            printf("Матрица вырождена, обратная матрица не существует.\n");
            free_matrix(augmented);
            exit(-1);
        }


        for (int j = 0; j < 2 * n; j++) {
            augmented.data[i][j] /= pivot;
        }

        for (int j = 0; j < n; j++) {
            if (j != i) {
                double factor = augmented.data[j][i];
                for (int k = 0; k < 2 * n; k++) {
                    augmented.data[j][k] -= factor * augmented.data[i][k];
                }
            }
        }
    }

    Matrix res = init(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res.data[i][j] = augmented.data[i][j + n]; 
        }
    }

    free_matrix(augmented);
    return res;
}

Matrix mat_E(int n) {
    Matrix res = init(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res.data[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
    return res;
}

int main() {
    srand(time(NULL));
    int n, m = 0;
    int choice = 0;
    double lambda = 0.0;
    
    printf("Введите размер матрицы:\n");
    printf("n = ");
    scanf("%d", &n);
    printf("m = ");
    scanf("%d", &m);
    printf("Введите скаляр λ с плавающей точкой\n");
    printf("λ = ");
    scanf("%lf", &lambda);
    
    Matrix a = init(n, m);
    Matrix b = init(n, m);

    printf("Выберите метод ввода матриц: \n1) заполнение рандомными числами \n2) заполнение с файла \n3) единичная матрица\n");
    printf("Выбор = ");
    scanf("%d", &choice);
    
    switch (choice)
    {
    case 1:
        mat_random(&a);
        mat_random(&b);
        break;
    
    case 2:
        read_from_file("matrix_fill_a.txt", a);
        read_from_file("matrix_fill_b.txt", b);
        break;
    case 3:
        /* отдельно по требованию преподавателя надо было обработать единичную матрицу (создать и вывести определитель)
           потому была создана отдельная ветка switch/case
        */
        Matrix E = mat_E(n);
        double deter_E = det(E);
        print_matrix(E);
        printf("\n");
        printf("Определитель единичной матрицы E: %f\n", deter_E);
        free_matrix(E);
        return 0;
    default: 
        printf("Неверный ввод!");
        exit(-1);
    }
    
    printf("Исходная матрица A: \n");
    print_matrix(a);

    printf("Исходная матрица B: \n");
    print_matrix(b);

    printf("\n");
    
    printf("Сумма матриц A и B: \n");
    Matrix sum_ab = sum(a, b);
    print_matrix(sum_ab);
    free_matrix(sum_ab);
    
    printf("\n");

    printf("A транспонированная:\n");
    Matrix trans_a = transpose(a);
    print_matrix(trans_a);
    free_matrix(trans_a);

    printf("B транспонированная:\n");
    Matrix trans_b = transpose(b);
    print_matrix(trans_b);
    free_matrix(trans_b);

    printf("\n");

    printf("\nA на скаляр %lf:\n", lambda);
    Matrix scalar_a = mult_on_scalar(a, lambda);
    print_matrix(scalar_a);
    free_matrix(scalar_a);

    printf("B на скаляр %lf:\n", lambda);
    Matrix scalar_b = mult_on_scalar(b, lambda);
    print_matrix(scalar_b);
    free_matrix(scalar_b);
    
    printf("\n");
    
    if(n == m) {
        double deter_a = det(a);
        double deter_b = det(b);
        printf("Определитель матрицы A: %lf\n", deter_a);
        printf("Определитель матрицы B: %lf\n", deter_b);
        
        
        printf("Обратная матрица A:\n");
        Matrix inv_a = invert(a);
        print_matrix(inv_a);
        free_matrix(inv_a);
        
        printf("Обратная матрица B:\n");
        Matrix inv_b = invert(b);
        print_matrix(inv_b);
        free_matrix(inv_b);
        
    } else {
        printf("Матрицы не квадратные, невозможно найти обратные матрицы.\n");
    }

    free_matrix(a);
    free_matrix(b);
    return 0;
}