#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
        int fp;
        if(argc <= 1)
        {
                printf("Error: No Input\n");
                exit(0);
        }
        else if((open(argv[1], O_RDONLY)) == -1)
        {
                int cmp = strcmp(argv[1], "-");
                int x = 1;
                if(cmp == 0) x = 2;
                char str[9];
                char str2[8];
                for(int y = x; y < argc; y++)
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
                        for(int e = 0; e < 8; e++)
                        {
                                str2[e] = str[e+1];
                                sum += (int)str[e];
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
        else if((fp = open(argv[1], O_RDONLY)) != 1)
        {
                (void)argc;
                char c;
                char str[9];
                char str2[8];
                int x = 0;

                while((read(fp, &c, 1)) != 0)
                {
                        if(c != ' ')
                        {
                                str[x] = c;
                                x++;
                        }
                        if(c == ' ')
                        {
                                //strcpy(str,argv[x]);
                                int sum = 0;
                                unsigned len = (unsigned)strlen(str);
                                if(len < 9)
                                {
                                        for(int y = len; y < 9; y++)
                                        {
                                                str[y] = '0';
                                        }
                                        str[8] = '\0';
                                }
                                for(int a = 0; a < 8; a++)
                                {
                                        str2[a] = str[a+1];
                                        sum+= (int)str[a];
                                }
                                char *ptr;
                                char ch = strtol(str2,&ptr,2);
                                int i = (int)ch;
                                printf("%s\t%c\t%i\t",str,ch,i);
                                if(sum % 2 == 0) printf("EVEN\n");
                                else printf("ODD\n");
                                x = 0;
                        }

                        //printf("%i",x);
                }
                //printf("%i",x);
        }
        else
        {
                printf("file did not open\n");
                exit(0);
        }
}
