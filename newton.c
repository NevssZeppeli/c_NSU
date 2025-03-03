#include <stdio.h>
#include <math.h>

// задача - решить уравнение F(X) = 0 методом Ньютона

double f(double x) {
    return x * x - 10 / sqrtf(100 - x);
}

double df(double x) {
    return ((2 * x) + 5/(sqrtf(100-x)*(100-x)));
}

double newton(double initial) {

    int iters = 0;
    int maxiters = 10000;
    double epsilon = 1e-6; // ограничение для разницы x_n и x_n1
    double delta = 1e-10; // ограничение для dfx на применимость метода

    while (iters < maxiters) {

        double fx = f(initial);
        double dfx = df(initial);
        
        if (fabs(dfx) < delta) {
            printf("Метод неприменим.\n");
            return NAN;
        }

        double new = initial - fx/dfx;
        
        if (fabs(new - initial) < epsilon) {
            printf("Найдено решение за %d итераций. \n", iters);
            return new;
        }

        initial = new;
        iters++;
        printf("%d: %f, %f\n", iters, fx, dfx);
    }
    
    return NAN;
}

void main() {

    double initial; // x_0

    printf("Введите начальную точку: \n");
    scanf("%lf", &initial);

    double root = newton(initial);
    if(!isnan(root)) printf("Корень уравнения F(X) = 0 равен: %lf\n", root);
    else printf("Решение не найдено, превышено количество итераций.\n");
    
}