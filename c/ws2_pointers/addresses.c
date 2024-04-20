#include <stdio.h>
#include <stdlib.h>

int main()
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *)malloc(sizeof (int) );
	int *ptr4 = (int *)malloc(sizeof (int) );
	if (ptr)
	{
		int **ptr3 = &ptr;
		printf("address of ptr3: %p\n", &ptr3);
	}
	
	
	
	printf("address of s_i: %p\n", &s_i);
	printf("address of i: %p\n", &i);
	printf("address of ptr: %p\n", ptr);
	printf("address of ptr: %p\n", ((int *)malloc(sizeof (int) )));
	printf("address of ptr2: %p\n", &ptr2);
	printf("address of ptr4: %p\n", &ptr4);

	
	
	return 0;
}
