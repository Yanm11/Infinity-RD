#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ENDIAN_BIG (*(short *)"\0xff" & 0xff) ? printf("Big\n") : printf("Little\n");

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
