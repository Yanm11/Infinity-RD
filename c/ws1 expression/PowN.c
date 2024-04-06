#include <stdio.h>


double PowN(int n);


int main()
{
	int n;
	printf("your number: ");
	scanf("%d", &n);
	
	
	double x = PowN(n);
	
	printf("10 in the power of %i is %f\n", n, x);
	return 0;
}




double PowN(int n)
{
	double x = 1;
	float multiplier = 10;
	
	if (n < 0)
	{
		n = -n;
		multiplier = 1/multiplier;
	}
	
	for (int i = 0; i < n; i++)
	{
		x *= multiplier;
	}
	
	return x;

}
