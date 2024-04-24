#include <stdio.h> /* printf sizeof */
#include <stdlib.h> /* realloc free */
#include <string.h> /* strlen */
#include <assert.h> /* assert */
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

void AddElem(arr_element_t *elem, int num)
{
	int new_size = (elem -> size * 4) + sizeof(num);
	elem -> array_int = (int *)realloc((elem -> array_int), new_size);
	new_size /= 4;
	assert (NULL != elem -> array_int);
	
	(elem -> array_int)[new_size - 1] = num;
	elem->size = new_size;
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

void PrintElem(arr_element_t *elem)
{
	int i = 0;
	for (;i < (elem->size); i++)
	{
		printf("%d,",elem->array_int[i]);
	}
	printf("\n");
}

void Clean(char **ptr)
{
	free(*ptr);
}

void CleanElem(arr_element_t *elem)
{
	free((elem -> array_int));
}

void DoNothing()
{
}
