#include <stdio.h>
#define MAX 128

/*
 * Read input from console.
 * x - address of variable where input should be stored
 */
void read_input(unsigned * x)
{
    printf("X = "); scanf("%u", x);
}

/*
 * Primality test.
 * x - the value to be tested
 * return 1 if x is prime else 0
 */
int is_prime(unsigned x)
{
    if (x <= 1) return 0;
    if (x <= 3) return 1;
    for (unsigned i = 2; i <= x / 2; ++i)
    {
        if (x % i == 0) return 0;
    }
    return 1;
}

/*
 * Find the next prime number greater than x.
 * x - the starting number
 * return the next prime number found
 */
unsigned next_prime(unsigned x)
{
    x += 1;
    while (!is_prime(x)) {
        x += 1;
    }
    return x;
}

/*
 * Decompose x in prime factors.
 * x - the value to be decomposed
 * factors - array where factors will be stored
 * powers - array where exponents will be stored
 * returns the number of prime factors which is the dimension of the arrays too
 */
unsigned decompose_in_prime_factors(unsigned x, unsigned factors[], unsigned powers[])
{
    unsigned n = 0, prime = 2, power;
    while (x > 1)
    {
        power = 0;
        while (x % prime == 0)
        {
            ++power;
            x = x / prime;
        }
        if (power)
        {
            powers[n] = power;
            factors[n] = prime;
            ++n;
        }
        prime = next_prime(prime);
    }
    return n;
}

/*
 * Print decomposition of a number given the factors and their exponents
 */
void print_decomposition(unsigned n, unsigned factors[], unsigned powers[])
{
    printf("X = ");
    for (unsigned i = 0; i < n; ++i)
    {
        printf("%d^%d", factors[i], powers[i]);
        if (i != n - 1) printf("*");
        else printf("\n");
    }
}

int main()
{
    unsigned x = 0, n = 0, factors[MAX], powers[MAX];
    read_input(&x);
    n = decompose_in_prime_factors(x, factors, powers);
    print_decomposition(n, factors, powers);
    return 0;
}
