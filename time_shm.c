/**
 * Austin Kim
 * time_shm.c -- Get time elapsed on a command using shared memory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/time.h>	// timeval
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <fcntl.h>

void printargs(char ** arr)
{
	printf("Args: ");
	while (*arr)
	{
		printf("%s ", *arr);
		arr++;
	}
	printf("\n");
}

int main(int argc, char ** argv)
{
	int status;
	pid_t pid;

	int fd;	// file descriptor 
	const char * name = "OS";

	struct timeval * interval;	// { start, end }
	struct timeval elapsed;
	const int SIZE = sizeof(struct timeval) * 2;

	if (argc == 1)
	{
		printf("Usage: ./%s <command [args ...]>\n", argv[0]);
		return 1;
	}
	argv++;

	fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(fd, SIZE);
	interval = (struct timeval *)
		mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
	pid = fork();
	if (pid == 0)	// child
	{
		gettimeofday(interval, 0);
		execvp(argv[0], argv);
		exit(0);
	}
	else	// parent
	{
		wait(&status);
		gettimeofday(interval + 1, 0);
	}
	
	timersub (interval + 1, interval, &elapsed);
	printf("\nElapsed time: %d.%06d seconds\n", 
			(int)elapsed.tv_sec, (int)elapsed.tv_usec);
	
	return 0;
}
