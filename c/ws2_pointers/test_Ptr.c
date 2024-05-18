#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Ptr.h"

int main (void)
{
	int num1 = 2;
	int num2 = 4;
	int ar[5] = {1,2,3,4,5};
	int *ar2 = ArrayCp(ar,5);
	int i = 0;
	size_t st1 = 30;
	size_t st2 = 50;
	size_t *ptr1 = &st1;
	size_t *ptr2 = &st2;
	char str[] = "1234!!4321";
	char s1[]= " hello       world            !      k   ";
	
	/* swap two int */
	printf("current value of num1: %d\ncurrent value of num2: %d\n",num1,num2);
	SwapInt(&num1, &num2);
	
	printf("new value of num1: %d\nnew value of num2: %d\n",num1,num2);
	
	/* copy to array */
	for (; i < 5; i++)
	{
		printf("original array[%d]: %d\ncopy array[%d]: %d\n**********\n",i,ar[i],i,ar2[i]);
	}
	free(ar2);
	
	/* print addresses of different varaible */
	PrintAddresses();
	
	/* swap 2 size_t */	
	printf("pst 1: %ld,st1:%ld pst 2: %ld\n",*ptr1,st1,*ptr2);
	
	swap2sizet((size_t *)&ptr1, (size_t *)&ptr2);
	
	printf("pst 1: %ld,st1:%ld pst 2: %ld\n",*ptr1,st1,*ptr2);
	
	/* palindrome ptr2 */
	if (palindrome(str))
	{
		printf("succsess! its palindrome\n");
	}
	else
	{
		printf("not palindrome\n");
	}
	
	/* remove whitespace */
	/*char *str = (char *)malloc(1000);*/
	/*char *s1 = (char*)malloc(100);*/
	printf("old string: %s\n", s1);
	RmEdg(s1);
	
	printf("new string: %s\n", s1);
	printf("new string: hello world!\n");
	
	return 0;
}
