#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
	pid_t child1;
	pid_t child2;
	//(void) argv;
	int fd[2];
	int argv1 = 0;

	if(argc < 2)
	{
		fprintf(stderr, "Not enough arguments\n");
		exit(EXIT_FAILURE);
	}

	if(pipe(fd) == -1)
	{
		fprintf(stderr, "Pipe failed\n");
		exit(EXIT_FAILURE);
	}

	child1 = fork();
	if(child1 < 0)
	{
		fprintf(stderr, "Error in forking.\n");
		exit(EXIT_FAILURE);
	}
	else if (child1 == 0)
	{
		//child1
		//printf("Child1: pid:%d, ppid:%d \n", getpid(), getppid());
		if(close(fd[WRITE]) == -1)
		{
			fprintf(stderr, "Error closing reading end of pipe.\n");
			exit(EXIT_FAILURE);
		}
		dup2(fd[READ],STDIN_FILENO);
		
		//tube /bin/cat filename , /usr/bin/head -2
		//7 argcs
		
		while(strcmp(argv[argv1],",")!=0)
		{
			argv1++;
		}
		char *newArgv1[argv1];
		for(int x = 0; x < argv1-1; x++)
		{
			newArgv1[x] = argv[x+1];
		}
		newArgv1[argv1-1] = NULL;
		char *en[] = {NULL};
		for(int x = argv1+1; x < argc; x++)
		{
			write(fd[WRITE],argv[x],strlen(argv[x])+1);
		}
		close(fd[WRITE]);
		execve(newArgv1[0], newArgv1, en);
		fprintf(stderr, "Error in execve.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		
		child2 = fork();
		if(child2 < 0)
		{
			fprintf(stderr, "Error in forking.\n");
			exit(EXIT_FAILURE);
		}
		else if(child2 == 0)
		{
			//child2
			//printf("Child2: pid:%d, ppid:%d \n", getpid(), getppid());
			dup2(fd[READ],STDOUT_FILENO);
			if(close(fd[WRITE]) == -1)
			{
				fprintf(stderr, "Error closing writing end of pipe.\n");
				exit(EXIT_FAILURE);
			}
			char *newArgv2[argc - argv1 -1];
			for(int x = argv1+1; x < argc-1; x++)
			{
				read(fd[READ],newArgv2[x],strlen(newArgv2[x])+1);
			}
			char *envp[] = {NULL};
			execve(newArgv2[0],newArgv2,envp);

		}
		else
		{
			//parent
			fprintf(stderr,"Parent: child1 pid:%d, child2 ppid:%d \n", child1, child2);
			close(fd[READ]);

			write(fd[WRITE],newArgv1,sizeof(newArgv1));
			write(fd[WRITE],newArgv2,sizeof(newArgv2));

			close(fd[WRITE]);
			int status1;
			int status2;

			waitpid(child1, &status1, 0);
			waitpid(child2, &status2, 0);

			fprintf(stderr, "%s: $? = %d\n",newArgv1[0], status1);
			fprintf(stderr, "%s: $? = %d\n",newArgv2[0], status2);
		}
	}

}
