#include <stdio.h> /* printf scanf */

#include "Expression.h"

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

