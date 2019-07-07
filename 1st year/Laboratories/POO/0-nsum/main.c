/*
 * main.c
 *
 *  Created on: Mar 1, 2018
 *      Author: alex
 */

#include <stdio.h>

void read_unsigned(unsigned int * p)
{
	printf("N = ");
	scanf("%u", p);
}

void read_ints(int * v, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("V[%d] = ", i);
		scanf("%d", v + i);
	}
}

int sum_ints(int * v, int n)
{
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += v[i];
	}
	return sum;
}

int main(void)
{
	int v[100];
	unsigned n;
	read_unsigned(&n);
	read_ints(v, n);
	printf("SUM = %d", sum_ints(v, n));
	return 0;
}

