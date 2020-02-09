#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
        if(argc <= 1)
        {
                printf("Error: No Input\n");
                exit(0);
        }
        if((open(argv[1], O_RDONLY)) == -1)
        {
                int cmp = strcmp(argv[1], "-");
                int x = 1;
                if(cmp == 0) x = 2;
                char str[9];
                char str2[8];
                for(int y = x; y < argc; x++)
                {
                        strcpy(str,argv[y]);
                        int sum = 0;
                        unsigned len = (unsigned)strlen(argv[y]);
                        if(len < 9)
                        {
                                for(int z = len; z < 9; z++)
                                {
                                        str[z] = '0';
                                }
                                str[8] = '\0';
                        }
                        for(int z = 0; z < 8; z++)
                        {
                                str2[z] = str[z+1];
                                sum += (int)str[z];
                        }
                        //char c = strtol(str2,0,2);
                        char *ptr;
                        char c = strtol(str2,&ptr,2);
                        int a = (int)c;

                        printf("%s\t%c\t%i\t",str,c,a);
                        if(sum % 2 == 0)
                        {
                                printf("EVEN\n");
                        }
                        else
                        {
                                printf("ODD\n");
                        }
                }
        }
}
