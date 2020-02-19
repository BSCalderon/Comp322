#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

void header();
void padRight(char *array, char *string);
void padRight2(char *string);
void printArray(char *ar);
int sum(char *array);
void copy7(char *dest, char *src);
void print(char *array, int decimal, char ascii);
int inputCheck(char *array);

const char *values[] = {"NUL","SOH","STX","ETX","EOT","ENQ","ACK","BEL",
				"BS","HT","LF","VT","FF","CR","SO","SI","DLE","DC1",
				"DC2","DC3","DC4","NAK","SYN","ETB","CAN","EM","SUB",
				"ESC","FS","GS","RS","US","SPACE"};

int main(int argc, char *argv[])
{
	char string[9];
	char string8[8];
	
	//conditional to check if number of arguments is valid
	if(argc <= 1)
	{
		printf("Error: No Input\n");
		exit(0);
	}
	//conditional to check if file exists
	else if(access(argv[1],F_OK) != -1)
	{
		//check file for any possible errors
		int file = open(argv[1], O_RDONLY);
		if(file >= 0)
		{
			char buffer[250];
			char ch;
			int count = -1;
			int index = 0;
			int ind = 0;
			char *rest;
			
			while(read(file,&ch,1) != 0)
			{
				buffer[index++] = ch;
				++count;
			}
			buffer[count] = '\0';

			header();
			for(int x = x; x <= count; x++)
			{
				if(buffer[x] != ' ')
				{
					string[ind++] = buffer[x];
				}
				if(buffer[x] == ' ' || buffer[x] == '\0')
				{
					padRight2(string);
					copy7(string8,string);
					char ascii = strtol(string8,&rest,2);
					int dec = (int)ascii;
					print(string,dec,ascii);

					ind = 0;
				}
			}
			
		}
		else
		{
			printf("error reading file\n");
		}
		
	}
	//conditional to check if 2nd is "-" or numbers
	else if(strcmp(argv[1],"-") == 0 || argv[1][0] == '0' || argv[1][0] == '1')
	{
		int index = 1;
		int flag = 0;
		char *rest;
		if(strcmp(argv[1],"-") == 0) { index = 2;}
		
		
		//loops through argv to make sure input is valid and sets flag to true
		for(int x = index; x < argc; x++)
		{
			flag = inputCheck(argv[x]);
			
		}
		//if the flag is true, enter calculations and printing
		if(flag == 1)
		{
			header();
			for(int x = index; x < argc; x++)
			{
				padRight(argv[x],string);
			
				copy7(string8,string);

				char ascii = strtol(string8,&rest,2);
				int dec = (int)ascii;
				print(string,dec,ascii);
			
			}
		}
		else
		{
			printf("Invalid input\n");
		}
	}
	else
	{
		printf("file does not exist or input is invalid\n");
	}
	return 0;
}
//functions

//prints out the header
void header()
{
	printf("Original ASCII    Decimal  Parity  \n");
	printf("-------- -------- -------- --------\n");
}
//organized printing of information
void print(char *array, int decimal, char ascii)
{
	if(decimal > 32 && decimal != 127)
	{
		printf("%s%9c%9i",array,ascii,decimal);
	}
	else if(decimal == 127)
	{
		printf("%s%9s%9i",array,"DEL",decimal);
	}
	else
	{
		printf("%s%9s%9i",array, values[decimal],decimal);
	}

	if(sum(array) % 2 == 0)
	{
		printf("%5s\n","EVEN");
	}
	else
	{
		printf("%4s\n","ODD");
	}
}
//pads an array with zeros
void padRight(char *array, char *string)
{
	unsigned len = (unsigned)strlen(array);
	strcpy(string,array);
	if(len < 9)
	{
		for(int x = len; x < 8; x++)
		{
			string[x] = '0';
		}
		string[8] = '\0';
	}
}

//pads an array with zeros, but with one parameter
void padRight2(char *string)
{
	unsigned len = (unsigned)strlen(string);
	
	if(len < 9)
	{
		for(int x = len; x < 8; x++)
		{
			string[x] = '0';
		}
		string[8] = '\0';
	}
}

//returns the sum of the arrays elements
int sum(char *array)
{
	int summ = 0;
	for(int x = 0; x < 8; x++)
	{
		summ += array[x] - '0';
	}
	return summ;
}

//copy 9 element array into 8 for conversion
void copy7(char *dest, char *src)
{
	for(int x = 0; x < 8; x++)
	{
		dest[x] = src[x+1];
	}
}

//prints array
void printArray(char *ar)
{
	
	for(int x = 0; x < 7; x++)
	{
		printf("%c",ar[x]);
	}
	printf("\n");
	
}

//checks through each argv and returns 0 if input is invalid
int inputCheck(char *array)
{
	unsigned length = (unsigned)strlen(array);
	int flag = 1;
	for(unsigned x = 0; x < length; x++)
	{
		if(array[x] != '0' && array[x] != '1')
		{
			flag = 0;
			return flag;
		}
	}
	return flag;
}
