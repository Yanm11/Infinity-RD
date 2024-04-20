#include <stdio.h>/* printf */

void Print(int x);

typedef void (*ptr_func)(int);
typedef struct print_me
{
  int i;
  ptr_func p;
} print_me;

int main(void)
{
	print_me arr[10];
	int i = 0;
	for (;i < 10; i++)
	{
		arr[i].i = i;
		arr[i].p = &Print;
	}
	
	for (i = 0; i < 10; i++)
	{
		arr[i].p(arr[i].i);
	}
	
	return 0;
}

void Print(int x)
{
	printf("%d\n", x);
}
