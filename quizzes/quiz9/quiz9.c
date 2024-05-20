#include <stdio.h>
#include <stdlib.h>

#define MAX2(a,b) ((a > b) ? (a) : (b))
#define MAX3(a,b,c) ((a > b) ? (MAX2(a,c)) : (MAX2(b,c)))
#define TO_LOWER(a) ((a > 'A' && a < 'Z') ? (a + 32) : (a))
#define OFFSET(s,f) ((char*)&f - (char*)&s)

struct test1
{
	int num;
	char ch1;
}s;

union test2
{
	int num;
	char arr[5];
}u;



int main()
{
	int x = 3, y = 5, z = 1;
	char ch = 'D';
	printf("%d\n", MAX3(x,y,z));
	printf("%c\n", TO_LOWER(ch));
	printf("%ld\n", (size_t)OFFSET(s, s.ch1));
	printf("%ld\n", sizeof(u));
	return 0;
}

