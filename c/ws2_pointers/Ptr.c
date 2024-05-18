#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Ptr.h"

void SwapInt(int *p1, int *p2)
{
	int p3 = *p1;
	*p1 = *p2;
	*p2 = p3;
}

int *ArrayCp(int array[], int size)
{
	int *ptr = (int*) malloc(size * sizeof(int));
	int i = 0;
	
	for (; i < size; i++)
	{
		ptr[i] = array[i];
	}
	
	return ptr;
}

void PrintAddresses()
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *)malloc(sizeof (int) );
	int *ptr4 = (int *)malloc(sizeof (int) );
	if (ptr)
	{
		int **ptr3 = &ptr;
		printf("address of ptr3: %p\n", (void*)&ptr3);
	}
	
	printf("address of s_i: %p\n",(void*) &s_i);
	printf("address of i: %p\n", (void*)&i);
	printf("address of ptr: %p\n", (void*)ptr);
	printf("address of ptr: %p\n", (malloc(sizeof (int) )));
	printf("address of ptr2: %p\n", (void*)&ptr2);
	printf("address of ptr4: %p\n", (void*)&ptr4);
}

void swap2sizet(size_t *num1, size_t *num2)
{
	size_t num3 = *num1;
	*num1 = *num2;
	*num2 = num3;
}

void swap2sizetp(size_t **num1, size_t **num2)
{
	size_t *num3 = *num1;
	*num1 = *num2;
	*num2 = num3;
}

int palindrome(char *str)
{
	char *start = str;
	char * end = str + strlen(str) - 1;
	
	while (*start)
	{
		if	(*start == *end)
		{
			++start, --end;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

void RmEdg(char *str) 
{
   
    char *ptr = str;
    while (*ptr && isspace(*ptr))
    {
        ptr++;
    }
    memmove(str, ptr, strlen(ptr) + 1); 
    
    
    ptr = str + strlen(str) - 1;
    while (ptr >= str && isspace(*ptr))
    {
        *ptr = '\0';
        ptr--;
    }
    
    WhiteSpace(str);
}


void WhiteSpace(char *str)
{
	char *ptr = str;
	char *space;
	
	while (*ptr)
	{	
		if (isspace(*ptr) && (isspace(*(ptr + 1)) || isspace(*(ptr-1))))
		{
			space = ptr;
			while (*space)
			{
				*space = *(space + 1);
				++space;
			}
			continue;
		}
		
		++ptr;
	}
}

