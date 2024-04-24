#include <stdio.h> /* printf */
#include <stdlib.h> /* size_t */
#define SIZEOF_VAR(var) ((size_t)(&(var)+1)-(size_t)(&(var)))
#define SIZEOF_TYPE(type) ((size_t)((type*)0 + 1) - (size_t)((type*)0))


int main(void)
{
	double x = 4.0;
	
	printf("size is: %ld\n", SIZEOF_VAR(x));
	printf("size of type double: %ld\n", SIZEOF_TYPE(double));
	return 0;
}
