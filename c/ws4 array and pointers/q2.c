#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void foo(int a[], int size)
{
	int i = 0;
	for (i = 0; i < size; ++i)
	{
		a[i] = i * 2;
	}
	printf("sizeof: %ld\n",sizeof(a));
}


int main(int argc, char **argv, char **envp)
{	
	char str[] = "welcome";
	int arr[10] = {0};
	foo (arr, 10);
	printf("sizeof: %ld\n",sizeof(arr));
	return (0);
}
