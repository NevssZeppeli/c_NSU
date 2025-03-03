#include <stdio.h>
#include <math.h>

double f(double x) {
    return x * x - 10 / sqrtf(100 - x);
}

double integral(double a, double b, int n) {
    double h = (b - a) / n;
    double s = 0;

    for(int i = 0; i < n; i++) {
        s += h * (f(a + i * h) + f(a + (i + 1) * h)) / 2;
    }
    
    return s;
}


void main () {

    double a, b;
    int n;

    printf("Введите границу a:\n");
    scanf("%lf", &a);
    printf("Введите границу b:\n");
    scanf("%lf", &b);
    printf("Введите количеств разбиейний:\n");
    scanf("%d", &n);

    printf("Площадь на отрезке a, b равен: %lf\n", integral(a, b, n));
}