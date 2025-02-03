#include <stdio.h>
#include <math.h>

void main() {

    float a, b, c;
    printf("Введите коэффициенты квадратного уравнения\n");
    
    printf("a: ");
    scanf("%f", &a);

    printf("b: ");
    scanf("%f", &b);

    printf("a: ");
    scanf("%f", &c);

    float d = b * b - (4 * a * c);
    
    if(d >= 0) {
        
        float x_1 = (-b + sqrtf(d))/(2*a);
        float x_2 = (-b - sqrtf(d))/(2*a);

        printf("\nКорни уравнения %f, %f \n", x_1, x_2);

    } else {
        printf("\nКорни - комплексные.\n");
    }
    


}