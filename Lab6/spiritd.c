#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<time.h>

int trigger = 0;
pid_t pidMoleChild;
int mole[2] = {0,0};

void handler(int number);
//static void daemon1();
int random();

int main(int argc, char *argv[])
{
     pid_t pid;
    struct rlimit rl;
    int fd0;
    int fd1;
    int fd2;
    char CPN[2];
    umask(0);
    if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
    {
        fprintf(stderr,"can't get file limit.\n");
        exit(EXIT_FAILURE);
    }


    pid = fork();

    if(pid < 0)
    {
        fprintf(stderr,"error in fork\n");
		exit(EXIT_FAILURE);
    }
    else if(pid != 0)
    {
        //parent
        exit(0);
    }
    setsid();
    if(chdir("/") < 0)
    {
        fprintf(stderr,"can't change directory.\n");
        exit(EXIT_FAILURE);
    }
    if(rl.rlim_max == RLIM_INFINITY)
    {
        rl.rlim_max = 1024;
    }
    for(int x = 0; x < rl.rlim_max; x++)
    {
        close(x);
    }
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    signal(SIGTERM, handler);
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    pidMoleChild = fork();
    

    while(1)
    {
        
        sleep(2);
        if(pidMoleChild == 0)
        {
            itoa(random(), CPN, 10);
            //execv the mole.c program
            char *argv2[] = {"mole.c", num, NULL};
            execv(argv2[0], ++argv2);
        }
    }
    
    
    return EXIT_SUCCESS;
}
// static void daemon1()
// {
//     pid_t pid;
//     struct rlimit rl;
//     int fd0;
//     int fd1;
//     int fd2;
//     char CPN[2];
//     umask(0);
//     if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
//     {
//         fprintf(stderr,"can't get file limit.\n");
//         exit(EXIT_FAILURE);
//     }


//     pid = fork();

//     if(pid < 0)
//     {
//         fprintf(stderr,"error in fork\n");
// 		exit(EXIT_FAILURE);
//     }
//     else if(pid != 0)
//     {
//         //parent
//         exit(0);
//     }
//     setsid();
//     if(chdir("/") < 0)
//     {
//         fprintf(stderr,"can't change directory.\n");
//         exit(EXIT_FAILURE);
//     }
//     if(rl.rlim_max == RLIM_INFINITY)
//     {
//         rl.rlim_max = 1024;
//     }
//     for(int x = 0; x < rl.rlim_max; x++)
//     {
//         close(x);
//     }
//     fd0 = open("/dev/null", O_RDWR);
//     fd1 = dup(0);
//     fd2 = dup(0);
//     signal(SIGTERM, handler);
//     signal(SIGUSR1, handler);
//     signal(SIGUSR2, handler);

//     pidMoleChild = fork();
//     itoa(random(), CPN, 10);
//     //execv the mole.c program
//     char *argv2[] = {"mole.c", num, NULL};
//     execv(argv2[0], ++argv2);
// }

void handler(int number)
{
  if(number == SIGTERM)
  {
      kill(pid, SIGTERM);
      exit(EXIT_SUCCESS);
  }
  else if(number == SIGUSR1)
  {
      if(pidMoleChild > 0)
      {
          kill(pidMoleChild, SIG)
      }
  }

}
int random()
{
    return (rand() % (2 - 1 + 1) + 1);
}