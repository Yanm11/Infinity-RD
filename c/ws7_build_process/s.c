#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

char *StrNcpy(char *dest, const char *src, size_t n)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	char *ptr1 = dest;
	
	while (*src && n)
	{
		*ptr1 = *src;
		++ptr1;
		++src;
		 --n;
	}
	
	return dest;
}

