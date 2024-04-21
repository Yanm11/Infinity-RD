#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "structs.h"
#include "user.h"


int main(void)
{
	char *p_str = NULL;
	any_element_t arr[3];
	int num_int = 4;
	float num_float = 5.7;
	
	any_element_t first;
	any_element_t second; 
	any_element_t third;
	
	p_str = (char*)malloc(12);
	assert (NULL != p_str);
	strcpy(p_str, "hello world");
	
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

	arr[0] = first;
	arr[1] = second;
	arr[2] = third;
	
	PrintAll(arr, 3);
	AddAll(arr, 3, 1500);
	PrintAll(arr, 3);
	CleanAll(arr, 3);
	
	return 0;
}
