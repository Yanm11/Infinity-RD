#include <stdio.h> /* sizeof */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* strcpy */
#include "structs.h"
#include "user.h"


int main(void)
{
	char *p_str = NULL;
	any_element_t arr[4];
	int num_int = 4;
	float num_float = 5.7;
	int *arr2 = NULL;
	int size = 3;
	
	arr_element_t arr_elem;
	any_element_t first;
	any_element_t second; 
	any_element_t third;
	any_element_t fourth;
	
	arr2 = (int*)malloc(sizeof(int)*size);
	p_str = (char*)malloc(12);
	if (NULL == arr2)
	{
		printf("NULL error malloc\n");
		exit(-1);
	}
	
	if (NULL == p_str)
	{
		printf("NULL error malloc\n");
		exit(-1);
	}
	
	strcpy(p_str, "hello world");
	
	arr_elem.array_int = arr2;
	arr_elem.size = size;
	
	arr2[0] = 1;
	arr2[1] = 2;
	arr2[2] = 3;
	
	first.element =  &num_int;
	first.add =  AddInt;
	first.print =  PrintInt;
	first.clean =  DoNothing;
	
	second.element = &num_float;
	second.add = AddFloat;
	second.print = PrintFloat;
	second.clean = DoNothing;
	
	third.element = &p_str;
	third.add = AddString;
	third.print = PrintString;
	third.clean = Clean;
	
	fourth.element = &arr_elem;
	fourth.add = AddElem;
	fourth.print = PrintElem;
	fourth.clean = CleanElem;

	arr[0] = first;
	arr[1] = second;
	arr[2] = third;
	arr[3] = fourth;
	
	PrintAll(arr, 4);
	AddAll(arr, 4, 100);
	PrintAll(arr, 4);
	CleanAll(arr, 4);
	
	return 0;
}
