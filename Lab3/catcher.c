#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

const int NUM = 29;
const char *signals[] = {"NULL", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE", "NULL", "SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM",
                        "SIGTERM", "SIGSTKFLT", "SIGCHLD", "SIGCONT", "NULL", "NULL", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH"};

int sigCount = 0;
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
        
        printf("%s caught at %ld\n", signals[number], seconds);
        
    }
    
   

}

int locateSig(char *sig)
{
    for(int x = 0; x < NUM; x++)
    {
        if(strcasecmp(signals[x],sig) == 0)
        {
            return x;
        }
    }
    printf("Error in locating signal\n");
    exit(EXIT_FAILURE);
}
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Too few arguments.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "%s: $$ = %d\n", argv[0], getpid());
    char sig1[10];
    char sig2[10];
    char sig3[10];
    
    strcpy(sig1, "SIG");
    strcpy(sig2, "SIG");
    strcpy(sig3, "SIG");

    strcat(sig1,argv[1]);
    strcat(sig2,argv[2]);
    strcat(sig3,argv[3]);

    signal(locateSig(sig1),handler);
    signal(locateSig(sig2),handler);
    signal(locateSig(sig3),handler);
    while(sigCount != 3)
    {
        pause();
       
    }
    exit(EXIT_SUCCESS);
}