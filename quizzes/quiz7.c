#include <stdio.h>

int CountCoupls(unsigned char c);
int CountBits(long n);

int main(void)
{
	unsigned char c = 255;
	long n = 1023;
	printf("number of couples of 1: %d\n", CountBits(n));
	return 0;
}


int CountCoupls(unsigned char c)
{
	int i = 0;
	int count = 0;
	
	for (; i < 7; i++)
	{
		if ((c & (1 << i)) && (c & (1 << (i + 1))))
		{
			++count;
		}
	}
	return count;
}

int CountBits(long n)
{
	int count = 0;
	
	while (n)
	{
		n = n & (n - 1);
		++count;	
	}
	return count;
}
