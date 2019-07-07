#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int sum = 0;
pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;

void* add_random (void* data)
{
	int x = rand() % 100;
	printf("(%lu) random = %i\n", pthread_self(), x);
	pthread_mutex_lock(&sum_mutex);
	sum += x;
	pthread_mutex_unlock(&sum_mutex);
	return NULL;
}

int main (void)
{
	int i;
	pthread_t threads[100];
	srand(65537);
	for (i = 0; i < 100; ++i)
	{
		if (pthread_create(&threads[i], NULL, add_random, NULL))
		{
			exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i < 100; ++i)
	{
		pthread_join(threads[i], NULL);
	}
	printf("SUM = %i\n", sum);
	return 0;
}
