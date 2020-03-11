#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("Not enough arguments...\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid;
	pid = fork();

	if(pid < 0)
	{
		printf("Error in forking...\n");
		exit(EXIT_FAILURE);
	}

	else if(pid == 0)
	{
		//Do child stuff
		//execve(program to launch, new argv for new program, envp{null})
		char *newArgv[argc-1];
		//argcOG = launch, newprogram, -ls, -r, null
		//newargc = newprogram, -ls, -r, null
		for(int x = 0; x < (argc - 1); x++)
		{
			newArgv[x] = argv[x+1];
		}
		char *en[] = {NULL};
		newArgv[argc-1] = NULL;
		execve(newArgv[0], newArgv, en);
		exit(EXIT_SUCCESS);
	}
	else
	{
		//Do parent stuff
		int status;
		fprintf(stderr, "%s: $$ = %u\n",argv[1], pid);
		waitpid(pid, &status, 0);
		fprintf(stderr, "%s: $? = %d\n",argv[1], status);
	}
	exit(EXIT_FAILURE);
}
