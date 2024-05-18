#include <stdio.h> /* printf scanf */

void HelloWorld();
double PowN(int n);
int Flip(int n);
void Swap(int *ptr1, int *ptr2);

int main(void)
{

	int n = 0;
	double x = 0;
	int y;
	int v1 = -150;
	int v2 = 580;
	
	/* print hello world */
	HelloWorld();
	
	/* pow of n */
	printf("your number: ");
	scanf("%d", &n);
	
	x = PowN(n);
	
	printf("10 in the power of %i is %f\n", n, x);
	
	/* flip */
	printf("The number you wish to flip: ");
	scanf("%d", &n);
	
	y = Flip(n);
	
	printf("%d flipped is: %d\n",n,y);
	
	/* swap */
	
	printf("v1: %d\nv2: %d\n",v1,v2);
	
	Swap(&v1, &v2);
	
	printf("v1: %d\nv2: %d\n",v1,v2);
	return 0;
}

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

