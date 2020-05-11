#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
    FILE *file;
    file = fopen("/home/stephen/lab6.log", "a");
    printf("\n entered mole");
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