#include <stdio.h>
#include <stdlib.h>

double Sqrt(double num)
{
	double x = (num + 1) / 2;
	double change = 0.00000000000000001;
	double tmp = x - 1;
	
	while (abs((int)(x-tmp)) > change)
	{
		tmp = x;
		x = 0.5 * (x + (num / x));
	} 
	
	return x;
}


int main(void)
{
	double num = 15862;
	
	printf("result of swrt %f is: %f\n", num, Sqrt(num));
	
	return 0;
}
