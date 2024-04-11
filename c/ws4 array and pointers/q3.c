#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char **argv, char **envp)
{	
	char *p = "lalala";
	char arr[10] = "lalala";
	++p;
	++arr;
	//*p = 's';
	//p[0] = 's';
	
	//arr[1] = 's';
	//*(arr+1) = 's';
	1[arr] = 's';
	printf("p is: %c \n", *p);
	
	return (0);
}
