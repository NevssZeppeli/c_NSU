#include <stdio.h>
#include <math.h>

double rounded(double number, int places) {

    double factored = pow(10, places);
    long int n_f = number*factored;
    return n_f / factored;

}


void main() {

    int places;
    int denom = 1;
    double pi = 0.0;
    double precision;
    double term;    
    double prev;
    double delta;
    double prev_delta;

    printf("Введите точность, с которой мы будем искать Пи: ");
    scanf("%d", &places);

    precision = 1.0 / pow(10, places);

    for (int k = 0; ; k++) {
        
        prev = pi;
        term = (k % 2 == 0 ? 1.0 : -1.0) / denom; // чередуем знак и получаем член ряда
        pi += term;
        denom += 2;        

        prev_delta = delta; 
        delta = (pi + prev) / 2;

        if (fabs(delta - prev_delta) <= precision/10000) break;

    }

    pi *= 4; // так как ряд лейбница-грегори дает pi/4, домножаем на 4
    prev *= 4;
    delta *= 4;
    
    double result = rounded(delta, places);
    printf("Число Пи с заданной точностью: %.*f\n", places, result);

}