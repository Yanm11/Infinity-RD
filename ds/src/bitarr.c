#include <stdio.h>

#include "bitarr.h"

bitarray_t SetAll(bitarray_t data)
{
	return (data = (size_t)-1);
}

bitarray_t ResetAll(bitarray_t data)
{
	return (data = (size_t)0);
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

bitarray_t Mirror(bitarray_t data)
{
	data = (data & 0xFFFFFFFF00000000) >> 32 | (data & 0x00000000FFFFFFFF) << 32;
	data = (data & 0xFFFF0000FFFF0000) >> 16 | (data & 0x0000FFFF0000FFFF) << 16;
	data = (data & 0xFF00FF00FF00FF00) >> 8 | (data & 0x00FF00FF00FF00FF) << 8;
	data = (data & 0xF0F0F0F0F0F0F0F0) >> 4 | (data & 0x0F0F0F0F0F0F0F0F) << 4;
	data = (data & 0xCCCCCCCCCCCCCCCC) >> 2 | (data & 0x3333333333333333) << 2;
	data = (data & 0xAAAAAAAAAAAAAAAA) >> 1 | (data & 0x5555555555555555) << 1;

	return data;
}

bitarray_t RotateRight(bitarray_t data, size_t rotate_value)
{
	size_t tmp = 0;
	size_t mask = 0xffffffffffffffff;
	mask = ~(mask << rotate_value);
	tmp = data & mask;
	tmp = tmp << (64 - rotate_value);
	data = data >> rotate_value;
	data = data | tmp;
	
	return data;
}

bitarray_t RotateLeft(bitarray_t data, size_t rotate_value)
{
	size_t tmp = 0;
	size_t mask = 0xffffffffffffffff;
	mask = ~(mask >>rotate_value);
	tmp = data & mask;
	tmp = tmp >> (64 - rotate_value);
	data = data << rotate_value;
	data = data | tmp;
	
	return data;
}

size_t CountOn(bitarray_t data)
{
	const size_t m1  = 0x5555555555555555; 
	const size_t m2  = 0x3333333333333333; 
	const size_t m4  = 0x0f0f0f0f0f0f0f0f; 
	const size_t m8  = 0x00ff00ff00ff00ff; 
	const size_t m16 = 0x0000ffff0000ffff; 
	const size_t m32 = 0x00000000ffffffff; 
	
	size_t x = data;

    x = (x & m1 ) + ((x >>  1) & m1 ); 
    x = (x & m2 ) + ((x >>  2) & m2 );
    x = (x & m4 ) + ((x >>  4) & m4 );
    x = (x & m8 ) + ((x >>  8) & m8 );
    x = (x & m16) + ((x >> 16) & m16);
    x = (x & m32) + ((x >> 32) & m32); 
    return x;
}

size_t CountOff(bitarray_t data)
{
	return (64 - CountOn(data));
}

char *ToString(bitarray_t data, char *buffer)
{
	char *ptr_start = buffer;
	size_t reminder = 0;
	size_t digits = 64;
	size_t quotient = 0;	
	
	quotient = data;
	
	buffer = buffer + digits - 1;
	quotient = data;
	
	while (quotient > 0)
	{
		reminder = quotient % 2;
		quotient = quotient / 2;
		
		*buffer = (char)(reminder + '0');
		--buffer;
	}
	
	while (buffer != ptr_start)
	{
		*buffer = '0';
		--buffer;
	}
	
	*buffer = '0';
	
	return ptr_start;
}
	
	
int CountBits(bitarray_t data)
{
	static int BitsSetTable256[256];
	int i = 0;
	
    BitsSetTable256[0] = 0; 
    for (; i < 256; i++)
    { 
        BitsSetTable256[i] = (i & 1) + BitsSetTable256[i / 2]; 
    } 
    
	return (BitsSetTable256[data & 0xff] + 
            BitsSetTable256[(data >> 8) & 0xff] + 
            BitsSetTable256[(data >> 16) & 0xff] + 
            BitsSetTable256[(data >> 24) & 0xff] + 
            BitsSetTable256[(data >> 32) & 0xff] + 
            BitsSetTable256[(data >> 40) & 0xff] + 
            BitsSetTable256[(data >> 48) & 0xff] + 
            BitsSetTable256[(data >> 56)]);
}

bitarray_t MirrorLut(bitarray_t data)
{
	static unsigned char lut[256];
	size_t i = 0;
	size_t j = 0;
	
	for (; i < 256; ++i)
	{
		unsigned char num = (unsigned char)i;
        unsigned char reversed = 0;
        for (j = 0; j < 8; ++j)
        {
            reversed <<= 1;
            reversed |= num & 1;
            num >>= 1;
        }
        lut[i] = reversed;
    }


    return (((size_t)lut[data & 0xff] << 56) |
            ((size_t)lut[(data >> 8) & 0xff] << 48) |
            ((size_t)lut[(data >> 16) & 0xff] << 40) |
            ((size_t)lut[(data >> 24) & 0xff] << 32) |
            ((size_t)lut[(data >> 32) & 0xff] << 24) |
            ((size_t)lut[(data >> 40) & 0xff] << 16) |
            ((size_t)lut[(data >> 48) & 0xff] << 8) |
            ((size_t)lut[(data >> 56) & 0xff]));
}




























