#include <stdio.h>
#include <stdlib.h>
int *ArrayCp(int array[], int size);

int main()
{
	int ar[5] = {1,2,3,4,5};
	int *ar2 = ArrayCp(ar,5);
	
	
	for (int i = 0; i < 5; i++)
	{
		printf("original array[%d]: %d\ncopy array[%d]: %d\n**********\n",i,ar[i],i,ar2[i]);
	}
	free(ar2);
	return 0;


}


int *ArrayCp(int array[], int size)
{
	int *ptr = (int*) malloc(size * sizeof(int));
	
	for (int i = 0; i < size; i++)
	{
		ptr[i] = array[i];
	}
	
	return ptr;
}
