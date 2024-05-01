#include <stdio.h>
#include "bitaaray.h"

bitarray_t SetAll(bitarray_t data)
{
	return (size_t)-1;
}

bitarray_t ResetAll(bitarray_t data)
{
	return (size_t)0;
}

bitarray_t SetBitOn(bitarray_t data, size_t index)
{
	data = data | (1 << index);
	
	return data;
}

bitarray_t SetBitOff(bitarray_t data, size_t index)
{
	data = data & (~(1 << index));
	
	return data;
}

bitarray_t SetBit(bitarray_t data, size_t index, int bool_value)
{
	data = (bool_value == 1) ? (SetBitOn(data,index)) : (SetBitOff(data,index));
	
	return data;
}

int GetVal(bitarray_t data, size_t index)
{
	return (data & (1 << index)) >> index;
}

bitarray_t FlipBit(bitarray_t data, size_t index)
{
	data = data ^ (1 << index);
	
	return data;
}

bitarray_t FlipAll(bitarray_t data)
{
	return ~data;
}






























