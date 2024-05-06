#include <stdio.h>

int checkPerfectNumber(int num);
double powerInt(double base, int exponent);

int main(void) {
    int p = 496;
    int n = 36;
    printf("checkPerfectNumber(%d) = %d\n", p, checkPerfectNumber(p));
    printf("checkPerfectNumber(%d) = %d\n", n, checkPerfectNumber(n));

    double b1 = -7.1, b2 = -3.0;
    int e1 = -4, e2 = 4;
    printf("powerInt(%f, %d) = %f\n", b1, e1, powerInt(b1, e1));
    printf("powerInt(%f, %d) = %f\n", b2, e2, powerInt(b2, e2));

    return 0;
}

int checkPerfectNumber(int num) {
    if (num <= 0) return 0;
    int sum = 0;
    for (int i = 1; i < num; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum == num ? 1 : 0;
}

double powerInt(double base, int exponent) {
    if (exponent == 0) {
        return 1;
    } else if (exponent < 0) {
        if (base == 0) {
            printf("Error: Division by zero\n");
            return 0; // Or handle more gracefully depending on your application
        }
        return 1 / powerInt(base, -exponent);
    } else {
        double result = 1;
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
        return result;
    }
}
