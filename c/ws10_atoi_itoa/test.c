#include <stdio.h> /* printf */ 
#include <stdlib.h> /* malloc free */ 
#include <string.h> /* strtol strcpy */ 
#include "ex1.h"


void Test(char *str, int base);
void Call_test(void);

int main(void)
{
	char arr1[] = {'a','b','d','f','z','t','s','d','%','s','s','s'};
	char arr2[] = {'a','b','d', 'f','t','d','%','l','l','l','s'};
	char arr3[] = {'a','c','e', 'f'};

	PrintOnly2Arr(arr1,arr2,arr3,sizeof(arr1),sizeof(arr2),sizeof(arr3));
	
	CheckIfLitEnd();
	
	printf("\n\nTest string to int:\n\n");
	Call_test();
	return 0;
}


void Test(char *str, int base)
{
	/* printf("my %ld\n", StrInt(str, base));
	printf("origin %ld\n", strtol(str, NULL, base)); */
	if (StrInt(str, base) == strtol(str, NULL, base))
	{
		printf("Test PASSED succesfuly\n");
	}
	else
	{
		printf("Test FAILED!!\n");
	}
}

void Call_test(void)
{
	char *str = (char*)malloc(20);
	/* for negative */
	int base = 10; 
	strcpy(str,"-1");
	printf("For negative:\n");
	Test(str, base);
	printf("------------------\n");
	
	/* for binary */
	base = 2; 
	printf("For binary:\n");
	Test(str, base);
	printf("------------------\n");
	
	/* for 36 */
	base = 36; 
	strcpy(str,"24heiz");
	printf("For base 36:\n");
	Test(str, base);
	printf("------------------\n");
	
	/* for 37 */
	base = 37; 
	strcpy(str,"24heiz");
	printf("For base 37:\n");
	Test(str, base);
	printf("------------------\n");
	
	/* for wrong input */
	base = 10; 
	strcpy(str,"24heiz");
	printf("For base wrong input:\n");
	Test(str, base);
	printf("------------------\n");
	
	/* for wrong input */
	base = 10; 
	strcpy(str,"24:257");
	printf("For another wrong input:\n");
	Test(str, base);
	printf("------------------\n");
	
	free(str);
	
}

