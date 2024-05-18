#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ws3.h"

int main(void)
{
	
	int arr[ROWS][COLS];
	int *arr2 = (int *)malloc(ROWS * sizeof(int));
	int i=0;
	int n;
	int num_env = 0;
	char **big_buffer = NULL;
	
	/* 2darr */
	func(arr,arr2);
	
	for (; i < ROWS; i++)
	{
		printf("%d, ",arr2[i]);
	}
	
	printf("\n");
	
	printf("sizeof array: %ld\n", sizeof(arr));
	free(arr2);
	
	/* josephus */
	printf("number of soldiers: ");
	scanf("%d", &n);
	
	printf("the soldier left standing is at index: %d \n", Josephus(n));
	

	/* env */
	for(; environ[num_env] != 0; num_env++){}
	
	big_buffer = (char **) malloc(num_env * sizeof(char *));
	
	if (big_buffer == NULL)
	{
		free(big_buffer);
		return 1;
	}
	
	Memory(big_buffer, num_env);
	
	
	for (i = 0; i < num_env; i++)
	{
		strcpy(big_buffer[i], environ[i]);
		
		ToLower(big_buffer[i]);
		
		printf("%s \n", big_buffer[i]);
		
	}
	
	for (i = 0; i < num_env; i++)
	{
		free(big_buffer[i]);
	}
	
	free(big_buffer);
	
	/* datatypes */
	printf("the size of char is: %ld \n", sizeof(char));
	
	printf("the size of short is: %ld \n", sizeof(short));
	
	printf("the size of unsigned short is: %ld \n", sizeof(unsigned short));
	
	printf("the size of int is: %ld \n", sizeof(int));
	
	printf("the size of unsigned int is: %ld \n", sizeof(unsigned int));
	
	printf("the size of long int is: %ld \n", sizeof(long int));
	
	printf("the size of unsigned long int is: %ld \n", sizeof(unsigned long int));

	printf("the size of float is: %ld \n", sizeof(float));
	
	printf("the size of double is: %ld \n", sizeof(double));
	
	printf("the size of long doublet is: %ld \n", sizeof(long double));

	return 0;
}


