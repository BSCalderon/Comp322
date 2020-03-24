#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

#define READ 0
#define WRITE 1

void separateArgv(char *argv[], char *newArgv1[], char *newArgv2[], int argv1, int argc)
{
	
	int a = 1;
	for(int x = 0; x < argv1-1; x++)
	{
		newArgv1[x] = argv[a++];
	}
	newArgv1[argv1-1] = NULL;
	for(int x = 0; x < argc-argv1-1; x++)
	{
		
		newArgv2[x] = argv[++a];
	}
	newArgv2[argc-argv1-1] = NULL;
}

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

	
	while(strcmp(argv[argv1],",")!=0)
	{
		argv1++;
	}
	char *newArgv1[argv1];
	char *en[] = {NULL};
	int argv2 = argc-argv1-1;
	char *newArgv2[argv2];
	char *envp[] = {NULL};
	separateArgv(argv,newArgv1, newArgv2, argv1, argc);
	
	
	
	
	
	child1 = fork();
	if(child1 < 0)
	{
		fprintf(stderr, "Error in forking.\n");
		exit(EXIT_FAILURE);
	}
	else if (child1 == 0)
	{
		//child1
		
		if(close(fd[WRITE]) == -1)
		{
			fprintf(stderr, "Error closing reading end of pipe.\n");
			exit(EXIT_FAILURE);
		}
		dup2(fd[READ],STDIN_FILENO);
		
	
		
		
		
		read(fd[READ],newArgv1,sizeof(newArgv1)+1);
		close(fd[WRITE]);
		execve(newArgv1[0], newArgv1, en);
		// if(execve(newArgv1[0], newArgv1, en) == -1)
		// {
		// 	fprintf(stderr, "Error in execve for child 1.\n");
		// 	exit(EXIT_FAILURE);
		// }
		
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
			dup2(fd[READ],STDIN_FILENO);
			if(close(fd[WRITE]) == -1)
			{
				fprintf(stderr, "Error closing writing end of pipe.\n");
				exit(EXIT_FAILURE);
			}
			read(fd[READ], newArgv2,sizeof(newArgv2)+1);
			execve(newArgv2[0], newArgv2, envp);
			//if(execve(newArgv2[0], newArgv2, envp) == -1)
			// {
			// 	fprintf(stderr, "Error in execve for child 2.\n");
			// 	exit(EXIT_FAILURE);
			// }
		}
		else
		{
			//parent
			
			fprintf(stderr, "%s: $$ = %d\n", newArgv1[0], child1);
			fprintf(stderr, "%s: $$ = %d\n", newArgv2[0], child2);
			close(fd[READ]);

			write(fd[WRITE],newArgv1,sizeof(newArgv1));
			write(fd[WRITE],newArgv2,sizeof(newArgv2));

			close(fd[WRITE]);
			int status1;
			int status2;

			waitpid(child1, &status1, 0);
			waitpid(child2, &status2, 0);

			fprintf(stderr, "\n%s: $? = %d\n",newArgv1[0], status1);
			fprintf(stderr, "%s: $? = %d\n",newArgv2[0], status2);
		}
	}

}
