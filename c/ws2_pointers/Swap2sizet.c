#include <stdio.h>
#include <stdlib.h>
void swap2sizet(size_t *num1, size_t *num2);
void swap2sizetp(size_t **num1, size_t **num2);

int main()
{
	size_t st1 = 30;
	size_t st2 = 50;
	size_t *ptr1 = &st1;
	size_t *ptr2 = &st2;
	
	printf("pst 1: %ld,st1:%ld pst 2: %ld\n",*ptr1,st1,*ptr2);
	
	swap2sizet((size_t *)&ptr1, (size_t *)&ptr2);
	
	printf("pst 1: %ld,st1:%ld pst 2: %ld\n",*ptr1,st1,*ptr2);





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
