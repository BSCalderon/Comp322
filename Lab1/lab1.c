#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/times.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	time_t _time;
	pid_t pid;
	pid_t w;
	struct tms cuTimes;
	_time = time(NULL);
	printf("START: %ld\n",_time);
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
		_time = time(NULL);
		times(&cuTimes);
		printf("PPID: %u, PID: %u, CPID: %u, RET: %d\n",getppid(),getpid(),pid,status);
		printf("USER: %jd, ",cuTimes.tms_utime);
		printf("SYS: %jd\n",cuTimes.tms_stime);
		printf("CUSER: %jd, ",cuTimes.tms_cutime);
		printf("CSYS: %jd\n",(cuTimes.tms_cstime));
		printf("END: %jd\n",_time);
		if(w == -1)
		{
			printf("waitpid error\n");
			exit(EXIT_FAILURE);
		}

	}

	exit(EXIT_SUCCESS);
	
}
