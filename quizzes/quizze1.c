#include <stdio.h> /* printf scan f */
 
int main(void)
{
	int num = 0;
	const int num2 = 6;
	const int num3 = num2 - 5;
	
	printf("num is %d write new value:\n", num);
	
	scanf ("%d", &num);
	
	printf ("100 divided by %d is %f \n", num, 100.0/num);
	
	printf("num3: %d \n", num3);
	
	num = 4;
	num = 2 * num;
	num++;
	
	return (0);
}
