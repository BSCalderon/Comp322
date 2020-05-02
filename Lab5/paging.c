#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    (void)argc;
    unsigned long input;
    input = atoi(argv[1]);
    const unsigned long KB4 = 4096;
    unsigned long page = input/KB4;
    unsigned long offset = input % KB4;
    printf("The address %lu contains:\n",input);
    printf("Page number = %lu\n",page);
    printf("offset = %lu\n",offset);
    return 0;
}
