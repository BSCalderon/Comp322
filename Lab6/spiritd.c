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
#include<limits.h>


static pid_t pidMoleChild;
static int num;
char cwd[PATH_MAX];
char path[300];
int randomNum()
{
    return (rand() % (2 - 1 + 1) + 1);
}
// const char *getPath()
// {
//     static char *f;
//     strcat(strcpy(f, getenv("HOME")), "/lab6.log");
//     return f;
// }
static void handler(int sig)
{
    
    signal(sig, handler);
    if(sig == SIGTERM)
    {
        kill(pidMoleChild, SIGKILL);
        exit(0);
    }
    else if (sig == SIGUSR1)
    {
        
        if(num == 0)
        {
            kill(pidMoleChild, SIGCHLD);
        }
        num = randomNum();
        char nums[20];
        sprintf(nums, "%d", num);
        
        char *argv2[] = {path, nums, NULL};
        pidMoleChild = fork();
        if(pidMoleChild == 0)
        {
            execv(argv2[0], argv2);
        }
        signal(SIGUSR1, handler);
    }
    else if(sig == SIGUSR2)
    {
        if(num == 1)
        {
            kill(pidMoleChild, SIGCHLD);
        }
        num = randomNum();
        char nums[20];
        sprintf(nums, "%d", num);
        char *argv2[] = {path, nums, NULL};
        pidMoleChild = fork();
        if(pidMoleChild == 0)
        {
            execv(argv2[0], argv2);
        }
        signal(SIGUSR2, handler);
    }
}
int main(int argc, char *argv[])
{
    int fd0;
    (void)argc;
    (void)argv;
    
    getcwd(cwd, sizeof(cwd));
    sprintf(path, "%s/mole", cwd);
    printf("%s\n", cwd);
    pid_t pid = fork();
    if(pid < 0)
    {
        fprintf(stderr, "Error in forking\n");
        exit(EXIT_FAILURE);
    }
    if(pid > 0)
    {
        exit(0);
    }

    umask(0);
    pid_t sid = setsid();
    if(sid < 0)
    {
        fprintf(stderr, "Error in setsid\n");
        exit(EXIT_FAILURE);
    }
    if(chdir("/") < 0)
    {
        exit(EXIT_FAILURE);
    }
    
    if(fd0 = open("/dev/null", O_RDONLY) < 0)
    {
        fprintf(stderr, "Error in dev/null opening\n");
        exit(EXIT_FAILURE);
    }
    dup2(fd0, STDIN_FILENO);
    dup2(fd0, STDOUT_FILENO);
    dup2(fd0, STDERR_FILENO);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    signal(SIGTERM, handler);
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    pidMoleChild = fork();

    while(1)
    {
        sleep(1);
        
      
    }
}