#include <stdio.h>
void SwapInt(int *p1, int *p2);



int main ()
{
	int num1 = 2;
	int num2 = 4;
	printf("current value of num1: %d\ncurrent value of num2: %d\n",num1,num2);
	SwapInt(&num1, &num2);
	
	printf("new value of num1: %d\nnew value of num2: %d\n",num1,num2);
	
	return 0;
	
}



void SwapInt(int *p1, int *p2)
{
	int p3 = *p1;
	*p1 = *p2;
	*p2 = p3;
}
