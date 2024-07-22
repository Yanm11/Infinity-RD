#include <string.h>
#include <stdio.h>
#include <assert.h> 

int ArrayToInt(char *str);

int main(void)
{
	char *str = "9";
	
	printf("int of str is: %d\n", ArrayToInt(str));
	
	return 0;
}

int ArrayToInt(char *str)
{
	int num = 0;
	int minus = 1;
	
	assert(str);
	
	if ('-' == *str)
	{
		minus = -1;
		++str;
	}
	
	while ('\0' != *str)
	{
		char c = *str - '0';
		
		if (0 > c || 9 < c)
		{
			return 0;
		}
		
		num *= 10;
		num += (int)c;
		
		++str;
	}	
	
	return (num * minus);
}
