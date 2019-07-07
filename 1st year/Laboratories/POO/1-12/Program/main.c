#include <stdio.h>

/*
 * Read input from console.
 * x, p - addresses of variables where input should be stored
 * x - base
 * p - exponent
 */
void read_input(double * x, unsigned * p)
{
    printf("X(double) = "); scanf("%lf", x);
    printf("P(unsigned) = "); scanf("%u", p);
}

/*
 * Compute base^exp using exponentiation squaring.
 * base - base number
 * exp - exponent number
 * return(double) - base^exp
 */
double natural_pow(double base, unsigned exp)
{
    double result = 1;
    while (exp)
    {
        if (exp % 2 == 1)
        {
            result *= base;
        }
        exp = exp / 2;
        base *= base;
    }
    return result;
}

int main()
{
    double x;
    unsigned p;
    read_input(&x, &p);
    printf("X^P = %lf\n", natural_pow(x, p));
    return 0;
}
