#include <stdio.h> /* printf */
#define MAX2(a,b) (a>b?a:b)
#define MAX3(a,b,c) (a>b?MAX2(a,c):MAX2(b,c))
int main(void)
{
	printf("max is: %d\n", MAX3(20,3,100));
	return 0;
}
