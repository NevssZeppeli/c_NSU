#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int minimum(int arr[], int n) {
    int min = *arr;
    for (int *pointer = arr + 1; pointer < arr + n; pointer++) {
        if (*pointer < min) {
            min = *pointer;
        }
    }
    return min;
}

int maximum(int arr[], int n) {
    int max = *arr;
    for (int *pointer = arr + 1; pointer < arr + n; pointer++) {
        if (*pointer > max) {
            max = *pointer;
        }
    }
    return max;
}

// решение через указатель
double avg(int arr[], int n) {
    if (n == 1) return 0;
    int mean = 0;
    int *pointer = arr;
    for (int *pointer = arr; pointer < arr + n; pointer++) {
        mean += (*pointer - mean) / (pointer - arr + 1);
    //  mean += (arr[i] - mean) / (i + 1) то же самое
    }
    return mean;
}

double RMS(int arr[], int n) {
    if (n == 1) {
        printf("RMS невозможно посчитать, так как количество элементов равно 1.\n");
    } else {

    double mean = avg(arr, n);
    double summ_sq_diff = 0.0;
    for (int *pointer = arr; pointer < arr + n; pointer++) {
        summ_sq_diff += pow((*pointer - mean), 2);
    }
    return sqrt(summ_sq_diff / (n - 1));
    }
    return NAN;
}

int main() { 
    int *arr;
    int n;

    printf("Введите размер динамического массива >= 0:\n");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Некорректный размер массива.\n");
        return 1;
    }

    arr = malloc(sizeof(int) *  n);

    printf("Введите элементы массива (целые числа):\n");
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
    }

    printf("Минимум: %d\n", minimum(arr, n));
    printf("Максимум: %d\n", maximum(arr, n));
    printf("Среднее значение: %.2f\n", avg(arr, n));
    printf("Среднеквадратичное отклонение: %.2f\n", RMS(arr, n));

    free(arr);
    return 0;
}