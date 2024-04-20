#include <stdio.h>
#include "g.h"
int foo(int n);

int main(void)
{
	printf("g_s: %d", g_s);
	printf("g_s: %d", foo(g_s));
	
	return 0;
}
