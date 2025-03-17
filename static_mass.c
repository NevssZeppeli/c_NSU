#include <stdio.h>
#include <math.h>

#define MAX_SIZE 100
int arr[MAX_SIZE];
int n; // актуальный размер массива

int minimum() {
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int maximum() {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/* решение через прямое обращение к arr[i]
double avg() {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (double)sum / n;
}
*/

// решение через указатель
double avg() {
    int sum = 0;
    int *pointer = arr; // Имя массива всегда хранит адрес самого первого элемента, который мы далее можем "сдвигать"
    
    for (int i = 0; i < n; i++) {
        sum += *pointer;
        pointer++;
    }
    
    return (double)sum / n;
}

double RMS() {
    
    if (n == 1) {
        printf("RMS невозможно посчитать, так как количество элементов равно 1.\n");
    } else {
    double mean = avg();
    double summ_sq_diff = 0.0;
    for (int i = 0; i < n; i++) {
        summ_sq_diff += pow((arr[i] - mean), 2);
    }
    return sqrt(summ_sq_diff / (n - 1));
    }

    return NAN;
}

int main() { 

    printf("Введите размер массива (более 1 и не более %d): ", MAX_SIZE);
    scanf("%d", &n);

    if (n > MAX_SIZE || n <= 0) {
        printf("Некорректный размер массива.\n");
        return 1;
    }

    printf("Введите элементы массива (целые числа):\n");
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
    }

    printf("Минимум: %d\n", minimum());
    printf("Максимум: %d\n", maximum());
    printf("Среднее значение: %.2f\n", avg());
    printf("Среднеквадратичное отклонение: %.2f\n", RMS());

    return 0;
}