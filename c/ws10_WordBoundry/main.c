#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"

int TestMemSet(char *str1, char *str2);
int TestMemCpy(char *str1, char *str2);
int TestMemMove(char *str1, char *str2);

int main(void)
{
	/* set the str to test memset */
	char *str_set1 = NULL;
	char *str_set2 = NULL;
	char c1 = '$';
	
	/* set the str to test memcpy */
	char *str_cpy1 = NULL;
	char *str_cpy2 = NULL;
	char *str_cpy3 = "helloworldworldhello";
	
	/* set the str to test memmove */
	char *str_dest1 = NULL;
	char *str_src1 = NULL;
	char *str_dest2 = NULL;
	char *str_src2 = NULL;

	/* set the str to test memset */
	str_set1 = (char *)malloc(21);
	str_set2 = (char *)malloc(21);
	strcpy(str_set1, "helloworldhelloworld");
	strcpy(str_set2, "helloworldhelloworld");
	
	/* set the str to test memcpy */	
	str_cpy1 = (char *)malloc(21);
	str_cpy2 = (char *)malloc(21);
	strcpy(str_cpy1, "hello");
	strcpy(str_cpy2, "hello");
	
	/* set the str to test memmove */	
	str_dest1 = (char *)malloc(21);
	str_src1 = str_dest1;
	str_dest2 = (char *)malloc(21);
	str_src2 = str_dest2;
	strcpy(str_dest1, "helloworldworldhello");
	strcpy(str_dest2, "helloworldworldhello");
	
	++str_dest1;
	++str_dest2;
	
	TestMemSet(MemSet(str_set1,c1,20),memset(str_set2,c1,20));
	TestMemCpy(MemCpy(str_cpy1,str_cpy3,14),memcpy(str_cpy2,str_cpy3,14));
	TestMemMove(MemMove(str_dest1,str_src1,10),memmove(str_dest2,str_src2,10));
	
	return 0;
}


int TestMemSet(char *str1, char *str2)
{
	if (strcmp(str1, str2) == 0)
	{
		printf("memset test PASSED\n");
		return 0;
	}
	
	else
	{
		printf("memset test FAILED\n");
		return -1;
	}
}

int TestMemCpy(char *str1, char *str2)
{
	if (strcmp(str1, str2) == 0)
	{
		printf("memcpy test PASSED\n");
		return 0;
	}
	
	else
	{
		printf("memcpy test FAILED\n");
		return -1;
	}
}

int TestMemMove(char *str1, char *str2)
{
	if (strcmp(str1, str2) == 0)
	{
		printf("memmove test PASSED\n");
		return 0;
	}
	
	else
	{
		printf("memmove test FAILED\n");
		return -1;
	}
}

