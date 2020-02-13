/**
 * Chris Nutter
 * Austin Kim
 * time_pipe.c -- get time elapsed of a command using pipes
 */

#include <stdio.h>
#include <stdlib.h> // exit()
#include <unistd.h>	// pid_t
#include <string.h>

#include <sys/time.h> // timeval
#include <sys/wait.h>	// wait


typedef struct timeval timeval_t;
const int SIZE = sizeof(timeval_t);

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		printf("Usage: ./%s <command [args ...]>\n", argv[0]);
		return 1;
	}
	argv++;

	int status;
	pid_t pid;

	int fd[2]; // file descriptor, fd[0]-> read-end, fd[1]-> write-end

	timeval_t begin, end, elapsed;

	if (pipe(fd) == -1)
	{
		printf("Pipe failed!\n");
		return 1;
	}

	pid = fork();
	if (pid == 0)	// child
	{
		close(fd[0]);	// don't need to read
		
		gettimeofday(&begin, 0);
		write(fd[1], &begin, SIZE);
		
		execvp(argv[0], argv);

		close(fd[1]);

		return 0;
	}
	else	// parent
	{
		close(fd[1]);	// don't need to write
		
		wait(&status);
		gettimeofday(&end, 0);
		read(fd[0], &begin, SIZE);

		close(fd[0]);
		timersub(&end, &begin, &elapsed);
	}

	printf("\nElapsed time: %d.%06d seconds\n", 
			(int)elapsed.tv_sec, (int)elapsed.tv_usec);

	return 0;
}
