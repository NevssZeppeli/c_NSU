#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void replace(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int compare_fwd(int a, int b) {
    return a > b;
}

int compare_bwd(int a, int b) {
    return a < b;
}

int compare_abs_fwd(int a, int b) {
    return abs(a) > abs(b);
}

int compare_abs_bwd(int a, int b) {
    return abs(a) < abs(b);
}

void bubble_sort(int *arr, int size, int(*compare)(int, int)) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (compare(arr[j], arr[j + 1])) {
                replace(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/* По заданию от преподавателя была написана сортировка сложностью O(n logn),
дело в том, что пузырьковая сортировка представляет собой O(n^2). 
Здесь написан сам алгоритм сортировки. Функция для его рекурсивного вызова ниже.*/

void merge(int *arr, int left, int mid, int right, int(*compare)(int, int)) {
    //размер левого и правого подмассива
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //левый и правый подмассив
    int* L = (int*)malloc(n1* sizeof(int));
    int* R = (int*)malloc(n2* sizeof(int));

    //переносим данные из arr в L, R
    for (int i = 0; i < n1; i++) 
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) 
        R[j] = arr[mid + 1 + j];
    
    //i - индекс для левого массива, j - индекс для правого массива, k - для итогового 
    int i = 0, j = 0, k = left;

    /* Проводим слиянием. Берем элемент из левого и правого массивов, проводим проверку.
    Если проверка дает True, в массив записывается элемент из L, иначе - из R */
    while (i < n1 && j < n2) {
        if (compare(L[i], R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Если, например, размер исходного массива является нечетным, то у нас могут остаться
    лишние элементы слева или справа. Для этого мы их допишем в arr */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(int *arr, int left, int right, int(*compare)(int, int)) {
    //здесь находим среднюю точку в массиве
    if (left < right) {
        int mid = left + (right - left) / 2;
        //сортируем левую и правую части массива
        merge_sort(arr, left, mid, compare);
        merge_sort(arr, mid + 1, right, compare);
        //когда обе части отсортированы - слияние
        merge(arr, left, mid, right, compare);
    }
}

void main() {
    int *arr;
    int n;
    int choice;
    int (*compare)(int, int);

    printf("Введите размер динамического массива > 0:\n");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Некорректный размер массива.\n");
        exit(1);
    }

    arr = malloc(sizeof(int) *  n);

    printf("Введите элементы массива (целые числа):\n");
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
    }

    printf("Выберите метод сортировки:\n1 - Возрастающая;\n2 - Убывающая;\n3 - По абс. значению возрастающая;\n4 - По абс. значению убывающая;\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        compare = compare_fwd;
        break;
    case 2:
        compare = compare_bwd;
        break;
    case 3:
        compare = compare_abs_fwd;
        break;
    case 4:
        compare = compare_abs_bwd;
        break;
    default:
        printf("Неверный ввод.\n");
        free(arr);
        break;
        exit(1);
    }

    printf("Выберите алгоритм сортировки:\n");
    printf("1 - пузырьковая сортировка\n");
    printf("2 - сортировка слиянием\n");
    
    int algorithm_choice;
    scanf("%d", &algorithm_choice);
    
    switch (algorithm_choice) {
        case 1:
            bubble_sort(arr, n, compare);
            break;
        case 2:
            merge_sort(arr, 0, n - 1, compare);
            break;
        default:
            printf("Неверный выбор алгоритма!\n");
            free(arr);
            exit(1);
    }

    bubble_sort(arr, n, compare);
    printf("Отсортированный массив: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
}