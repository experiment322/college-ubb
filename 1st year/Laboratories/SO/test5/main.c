#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define R 0
#define W 1
#define RW 2
#define BUF_SIZE 256

int main(void)
{
	int pid;
	int fd[RW];
	char s1[BUF_SIZE], s2[BUF_SIZE];
	if (pipe(fd) == -1)
	{
		perror("Pipe creation failed");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	switch (pid)
	{
		case -1: // pipe creation failed
			{
				perror("Fork creation failed");
				exit(EXIT_FAILURE);
			}
		case 0: // child process
			{
				close(fd[W]);
				while (1)
				{
					read(fd[R], s1, BUF_SIZE);
					if (strcmp(s1, "stop") == 0) break;
					read(fd[R], s2, BUF_SIZE);
					printf("Sirurile%s sunt identice\n", strcmp(s1, s2) == 0 ? "" : " nu");
				}
				close(fd[R]);
				break;
			}
		default: // parent process
			{
				close(fd[R]);
				while (1)
				{
					printf("S1: ");
					fgets(s1, BUF_SIZE, stdin);
					s1[strcspn(s1, "\n")] = '\0';
					write(fd[W], s1, BUF_SIZE);
					if (strcmp(s1, "stop") == 0) break;
					printf("S2: ");
					fgets(s2, BUF_SIZE, stdin);
					s2[strcspn(s2, "\n")] = '\0';
					write(fd[W], s2, BUF_SIZE);
					sleep(1);
				}
				close(fd[W]);
				wait(NULL);
				break;
			}
	}
	return 0;
}
