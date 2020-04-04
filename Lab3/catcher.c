#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

const int NUM = 29;
const char *signals[] = {"NULL", "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "BUS", "FPE", "NULL", "USR1", "SEGV", "USR2", "PIPE", "ALRM",
                        "TERM", "STKFLT", "CHLD", "CONT", "NULL", "NULL", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF", "WINCH"};

int sigCount = 0;

void handler(int number);
int locateSig(char *sig);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Too few arguments.\n");
        exit(EXIT_FAILURE);
    }
	
    for(int x = 1; x < argc; x++)
    {
		int s = locateSig(argv[x]);
		if(s == -1) 
		{
			fprintf(stderr,"Error in locating signal\n");
    		exit(EXIT_FAILURE);
		}
		signal(s,handler);
    }

    fprintf(stderr, "%s: $$ = %d\n", argv[0], getpid());
      
    while(sigCount != 3)
    {
        pause();
       
    }
    exit(EXIT_SUCCESS);
}
//function to locate signal integer from argv string
int locateSig(char *sig)
{
    for(int x = 0; x < NUM; x++)
    {
        if(strcasecmp(signals[x],sig) == 0)
        {
            return x;
        }
    }
	//if can't locate proper signal.
    return -1;
}
//handler function
void handler(int number)
{
    static int total = 0;
    time_t seconds;
    seconds = time(NULL);
    signal(number,handler);
    total++;
    if(number == SIGTERM)
    {
        sigCount++;
    }
    else
    {
        sigCount = 0;
    }
    
    if(sigCount == 3)
    { 
        fprintf(stderr,"catcher: Total signals count = %d\n",total);  
    }
    else
    {
        
        printf("SIG%s caught at %ld\n", signals[number], seconds);
        
    }
    
}