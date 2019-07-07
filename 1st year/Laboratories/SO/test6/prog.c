#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100
#define TNO 2
#define INFILE "random-file"

static int sum;
static int numbers[N];
static pthread_mutex_t sum_mtx = PTHREAD_MUTEX_INITIALIZER;

void* tfunc(void* arg)
{
	int i, n;
	n = *(int*)arg;
	free(arg);
	for (i = n; i < n + N / TNO; ++i)
	{
		pthread_mutex_lock(&sum_mtx);
		sum += numbers[i];
		pthread_mutex_unlock(&sum_mtx);
	}
	return NULL;
}

int main(void)
{
	int* n;
	int i, fd;
	pthread_t threads[TNO];
	fd = open(INFILE, O_RDONLY);
	for (i = 0; i < N; ++i)
	{
		read(fd, &numbers[i], 2);
	}
	close(fd);
	for (i = 0; i < TNO; ++i)
	{
		n = malloc(sizeof(*n));
		*n = i * (N / TNO);
		pthread_create(&threads[i], NULL, tfunc, n);
	}
	for (i = 0; i < TNO; ++i)
	{
		pthread_join(threads[i], NULL);
	}
	printf("%i\n", sum);
	return 0;
}

