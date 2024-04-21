#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <assert.h>
#include "structs.h"


void AddInt(int *ptr_int, int num)
{
	*ptr_int += num;
}

void AddFloat(float *ptr_float, int num)
{
	*ptr_float += num;
}

void AddString(char **ptr, int num)
{
	int len = strlen(*ptr);
	int new_size = strlen(*ptr)*sizeof(char) + sizeof(num) + 1;
	*ptr = (char *)realloc(*ptr,new_size);
	
	assert (NULL != *ptr);
	
	sprintf(*ptr + len, "%d", num);
}

void PrintInt(int *ptr)
{
	printf("%d\n", *ptr);
}

void PrintFloat(float *ptr)
{
	printf("%f\n", *ptr);
}

void PrintString(char **ptr)
{
	printf("%s\n", *ptr);
}

void Clean(char **ptr)
{
	free(*ptr);
}

void DoNothing()
{
}
