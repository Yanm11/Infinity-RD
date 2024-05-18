#include <stdio.h> /* printf scanf */

#include "Expression.h"

void HelloWorld()
{
	char s[15] = {0x22, 0x48,0x65, 0x6c, 0x6c, 0x6f, 0x20,0x57, 0x6f, 0x72, 0x6c
				  ,0x64, 0x21, 0x22,0};
	printf("%s\n",s);
}

double PowN(int n)
{
	double x = 1;
	float multiplier = 10;
	int i = 0;
	
	if (n < 0)
	{
		n = -n;
		multiplier = 1/multiplier;
	}
	
	for (;i < n; i++)
	{
		x *= multiplier;
	}
	
	return x;

}

int Flip(int n)
{
	int fliped = 0;
	
	while (n)
	{
		fliped *= 10;
		fliped += n % 10;
		n = n / 10;
	}
	
	return fliped;
}

void Swap(int *ptr1, int *ptr2)
{
	int v3 = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = v3;
}

