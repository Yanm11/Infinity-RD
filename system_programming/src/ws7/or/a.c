#include <stdio.h>

void Foo(void)
{
	printf("%d\n", 5);
	printf("%p\n", Foo);
	sleep(100);
}
