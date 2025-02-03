#include <stdio.h>
#include <math.h>

int is_prime(int n) {
    
    float sq = sqrt(n);

    for(int x = 2; x <= sq; x++) {
        if (n % x) {
            continue;
        } else {
            return -1;
        }
    }

    return 0;
}

void main() {

    int number;
    
    printf("Введите натуральное число, до которого мы выведем все простые числа: ");
    scanf("%d", &number);

    for(int x = 2; x <= number; x++) {
        if (is_prime(x) == 0) {
            printf("%d\n", x);
        }
    }

}