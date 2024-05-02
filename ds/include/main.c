#include <stdio.h>

struct
{
	int num;
	char ch1;
}s1;

int main(void)
{
	s1.num = 20;
	printf("%d\n", s1.num);
	return 0;
}
