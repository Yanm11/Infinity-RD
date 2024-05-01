#include <stdio.h>
#include "bitaaray.h"


int main(void)
{
	bitarray_t arr = 20;
	printf("Set all: %ld\n", SetAll(arr));
	printf("Reset all: %ld\n", ResetAll(arr));
	printf("Set bit on: %ld\n", SetBitOn(arr,2));
	printf("Set bit off: %ld\n", SetBitOff(arr,0));
	printf("Set bit on/off: %ld\n", SetBit(arr,0,0));
	printf("Get val: %d\n", GetVal(arr,4));
	printf("Fip bit: %ld\n", FlipBit(arr, 0));
	printf("Fip all: %ld\n", FlipAll(arr));
	
	return 0;
}
