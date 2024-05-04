#include <stdio.h>
#include <stdlib.h>
#include "bitaaray.h"


int main(void)
{
	bitarray_t arr = 1;
	char *buffer = (char*)calloc(65,1);
	if (NULL == buffer)
	{
		printf("error malloc\n");
		return -1;
	}
	
	printf("Set all: %ld\n", SetAll(arr));
	printf("Reset all: %ld\n", ResetAll(arr));
	printf("Set bit on: %ld\n", SetBitOn(arr,2));
	printf("Set bit off: %ld\n", SetBitOff(arr,0));
	printf("Set bit on/off: %ld\n", SetBit(arr,0,0));
	printf("Get val: %d\n", GetVal(arr,4));
	printf("Fip bit: %ld\n", FlipBit(arr, 0));
	printf("Fip all: %ld\n", FlipAll(arr));
	printf("Mirror: %ld\n", Mirror(arr));
	printf("Rotation: %ld\n", RotateRight(arr,0));
	printf("Rotation: %ld\n", RotateLeft(arr,0));
	printf("Count on: %ld\n", CountOn(arr));
	printf("Count off: %ld\n", CountOff(arr));
	printf("String: %s\n", ToString(arr, buffer));
	printf("Count LUT: %d\n", CountBits(arr));
	printf("Mirror LUT: %ld\n", MirrorLut(arr));
	
	
	free(buffer);
	
	return 0;
}
