#include "structs.h"

void PrintAll(any_element_t arr[], int size)
{
	int i = 0;
	
	for (; i < size; i++)
	{
		arr[i].print(arr[i].element);
	}
}

void AddAll(any_element_t arr[], int size, int num)
{
	int i = 0;
	
	for (; i < size; i++)
	{
		arr[i].add(arr[i].element, num);
	}
}

void CleanAll(any_element_t arr[], int size)
{
	int i = 0;
	
	for (; i < size; i++)
	{
		arr[i].clean(arr[i].element);
	}
}
