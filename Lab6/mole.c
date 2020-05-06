#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
    FILE *file;
    file = fopen("~/lab6.log", "w") ;
    if(strcmp(argv[1],"1") == 0)
    {
        fputs("Pop mole1", file);
    }
    else
    {
        fputs("Pop mole2", file);
    }
    fputs(argv[0], file);
    fclose(file);
    return 0;
}