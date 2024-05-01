#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/* ex4 */
#define ENDIAN_BIG (*(short *)"\0xff" & 0xff) ? printf("Big\n") : printf("Little\n");

static  int char_lut[256] = {0};

int ConvertCharInt(char *str, int base)
{
	if (*str >= 'a' && *str <= 'z' && base >= 11)
	{
		return (96 - 9);
	}
	else if (*str >= 'A' && *str <= 'Z' && base >= 11)
	{
		return (64 - 9);
	}
	else if (*str >= '0' && *str <= '9' && (base - ((int)*str-48)) > 0)
	{
		return 48;
	}
	
	return -1;
}

int ConvertIntChar(int num)
{
	if (num >= 0 && num <= 9)
	{
		return 48;
	}
	else if  (num >= 10)
	{
		return 64 - 9;
	}
	return 0;
	
}


long StrInt(char *str,int base)
{
	long sum = 0;
	int num = 0;
	int len = strlen(str);
	int sign = 1;
	int convert = 0;
	
	if (base > 36)
	{
		return (sign*sum);
	}

	if (*str == '-')
	{
		sign = -1;
		++str;
		--len; 
	}
	

	while (len > 0)
	{
		convert = ConvertCharInt(str, base);
		if (convert == -1)
		{
			return (sign*sum);
		}

		num = (int)*str - convert;
		sum *= base;
		sum += num;
		++str;
		--len;
	}
	
	return (sign*sum);
}

char *IntStr(char *str, int num, int base)
{
	char *ptr_start = str;
	int reminder = 0;
	int digits = 0;
	int quotient = 0;
	int convert = 0;
	
	if (num < 0)
	{
		num = -num;
		*str = '-';
		digits = 1;
	}
	
	quotient = num;
	
	while (quotient > 0)
	{
		++digits;
		quotient = quotient / base;
	}
	
	str = str + digits - 1;
	quotient = num;
	
	while (quotient > 0)
	{
		reminder = quotient % base;
		quotient = quotient / base;
		
		convert = ConvertIntChar(reminder);
		
		*str = (char)(reminder + convert);
		--str;
	}
	
	return ptr_start;
}

/* ex2 */

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

/* ex3 */
void CheckIfLitEnd()
{
	int n = 1;
	ENDIAN_BIG;
	if(*(char *)&n == 1)
	{
		printf("System is LITTLE endian\n");
	}
	
	else
	{
		printf("System is BIG endian");
	}

}


