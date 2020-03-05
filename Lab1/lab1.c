#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/times.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
void printTimes(struct tms Times);
int main()
{
	time_t _time;
	pid_t pid;
	pid_t w;
	struct tms cuTimes;
	_time = time(NULL);
	printf("START: %ld\n",_time);
	//Create child process.
	pid = fork();

	//If pid return a negative number, failure.
	if(pid < 0)
	{
		printf("error in fork\n");
		exit(EXIT_FAILURE);
	}

	//If pid returns 0, the child was successful.
	//Enter child block.
	else if(pid == 0)
	{
		printf("PPID: %u, PID: %u\n",getppid(),getpid());
		exit(EXIT_SUCCESS);
		
	}
	//Enter parent block
	else
	{
		
		int status;
		w = waitpid(pid,&status,0);
		if(w == -1)
		{
			printf("waitpid error\n");
			exit(EXIT_FAILURE);
		}
		_time = time(NULL);
		times(&cuTimes);
		printf("PPID: %u, PID: %u, CPID: %u, RET: %d\n",getppid(),getpid(),pid,status);
		printTimes(cuTimes);
		printf("END: %jd\n",_time);
	}

	exit(EXIT_SUCCESS);
	
}


void printTimes(struct tms Times)
{
	printf("USER: %jd, ",Times.tms_utime);
	printf("SYS: %jd\n",Times.tms_stime);
	printf("CUSER: %jd, ",Times.tms_cutime);
	printf("CSYS: %jd\n",Times.tms_cstime);
}
