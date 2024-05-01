#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static  int char_lut[256] = {0};


void CreateLUT(char *arr, size_t size)
{
	size_t i = 0;
	
	for (;i < size; ++i)
	{
		char_lut[(int)arr[i]] = -1;
	}
}

void PrintOnly2Arr(char *arr1, char *arr2, char *arr3, size_t size1, size_t size2, size_t size3)
{
	size_t i = 0;
	CreateLUT(arr3, size3);

	for (;i < size1; ++i)
	{
		if (char_lut[(int)arr1[i]] == 0 && isalpha(arr1[i]) > 0)
		{
			char_lut[(int)arr1[i]] = 1;
		}
	}
	
	for (i = 0; i < size2; ++i)
	{
		if (char_lut[(int)arr2[i]] == 1 && isalpha(arr2[i]) > 0)
		{
			char_lut[(int)arr2[i]] += 1;
		}
	}
	
	for (i = 0; i < 256; ++i)
	{
		if (char_lut[i] > 1)
		{
			printf("'%c',",(char)i);
		}
	}
	
	printf("\n");
}





