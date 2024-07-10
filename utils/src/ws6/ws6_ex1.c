#include <stdio.h>

#include "ws6_ex1.h"

int x = 40;

void PrintGlobalVariableAddress()
{
	printf("global x address is at: %p\n", &x);
}
