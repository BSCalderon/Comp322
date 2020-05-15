#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>
int main(int argc, char *argv[])
{
    (void)argc;
    
    FILE *file;
    char *filename = "/lab6.log";
    char *f;
    f = malloc(strlen(getenv("HOME") + strlen(filename) + 1));
    strcpy(f,getenv("HOME"));
    strcat(f, filename);
    //strcat(strcpy(f, getenv("HOME")), "/lab6.log");
    file = fopen(f, "a");
    
    if(!file)
    {
        perror("Error\n");
    }
    if(strcmp(argv[1],"1") == 0)
    {
        fprintf(file,"Pop mole1\n");
    }
    else
    {
        fprintf(file, "Pop mole2\n");
    }
    fclose(file);
    return 0;
}