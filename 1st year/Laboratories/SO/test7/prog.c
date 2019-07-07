#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>

#define NUMS 2000
#define THREAD_NO 20
#define NUMS_PER_THREAD (NUMS / THREAD_NO)

int numbers[NUMS];

int global_min = INT_MAX;
int global_max = INT_MIN;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void * func(void* arg)
{
	int i;
	int start = *(int *)arg;
	free(arg);
	for (i = start; i < start + NUMS_PER_THREAD; ++i)
	{
		if (numbers[i] % 2 == 0)
		{
			pthread_mutex_lock(&mtx);
			global_min = numbers[i] < global_min ? numbers[i] : global_min;
			global_max = numbers[i] > global_max ? numbers[i] : global_max;
			pthread_mutex_unlock(&mtx);
		}
	}
	return NULL;
}

void read_numbers()
{
	int i;
	int fd = open("test-file", O_RDONLY);
	if (fd == -1)
	{
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < NUMS; ++i)
	{
		read(fd, &numbers[i], 2);
	}
	if (close(fd) == -1)
	{
		exit(EXIT_FAILURE);
	}
}

int main(void)
{
	int i;
	int* start;
	pthread_t threads[THREAD_NO];
	read_numbers();
	for (i = 0; i < THREAD_NO; ++i)
	{
		start = malloc(sizeof (*start));
		*start = i * NUMS_PER_THREAD;
		if (pthread_create(&threads[i], NULL, func, start) != 0)
		{
			exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i < THREAD_NO; ++i)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			exit(EXIT_FAILURE);
		}
	}
	printf("%i - %i = %i\n", global_max, global_min, global_max - global_min);
	return 0;
}
