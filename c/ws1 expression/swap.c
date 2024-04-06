#include <stdio.h>
void Swap(int *ptr1, int *ptr2);

int main()
{
	int v1 = -150 , v2 = 580;
	
	printf("v1: %d\nv2: %d\n",v1,v2);
	
	Swap(&v1, &v2);
	
	printf("v1: %d\nv2: %d\n",v1,v2);
	
	return 0;

}




void Swap(int *ptr1, int *ptr2)
{
	int v3 = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = v3;
}

