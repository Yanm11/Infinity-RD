#ifndef __BITARR_H__
#define __BITARR_H__
#include <stddef.h>
typedef size_t bitarray_t;

/*
SetAll
turn all bits to 1
recieve an array of bits
return an array of bits
time O(1)
space O(1)
*/
bitarray_t SetAll(bitarray_t data);

/*
ResetAll
turn all bits to 0
recieve an array of bits
return an array of bits
time O(1)
space O(1)
*/
bitarray_t ResetAll(bitarray_t data);

/*
SetBitOn
turn a specific bit to 1
recieve an array of bits and an index
return array of bits
time O(1)
space O(1)
*/
bitarray_t SetBitOn(bitarray_t data, size_t index);

/*
SetBitOff
turn a specific bit to 0
recieve an array of bits and an index
return array of bits
time O(1)
space O(1)
*/
bitarray_t SetBitOff(bitarray_t data, size_t index);

/*
SetBit
turn specific bit to bool_value
recieve an array of bits, an index and a bool value
return array of bits
time O(1)
space O(1)
*/
bitarray_t SetBit(bitarray_t data, size_t index, int bool_value);

/*
GetVal
returns specific bit value
recieve an array of bits and an index 
returns a boolian value
time O(1)
space O(1)
*/
int GetVal(bitarray_t data, size_t index);

/*
FlipBit
flip a bit to the other value (1 -> 0 / 0 -> 1)
recieve an array of bits and an index 
return 
time O(1)
space O(1)
*/
bitarray_t FlipBit(bitarray_t data, size_t index);

/*
FlipAll
flip all bits to the other value (1 -> 0 / 0 -> 1)
recieve an array of bits
return array of bits
time O(1)
space O(1)
*/
bitarray_t FlipAll(bitarray_t data);

/*
Mirror
mirror an array of bits (10011 -> 11001)
recieve an array of bits
return array of bits
time O(1)
space O(1)
*/
bitarray_t Mirror(bitarray_t data);

/*
RotateRight
shift the array to the right
recieve an array of bits and number of times to shift
return array of bits
time O(1)
space O(1)
*/
bitarray_t RotateRight(bitarray_t data, size_t rotate_value);

/*
RotateLeft
shift the array to the left
recieve an array of bits and number of times to shift
return array of bits
time O(1)
space O(1)
*/
bitarray_t RotateLeft(bitarray_t data, size_t rotate_value);

/*
CountOn
count number of bits that are turned on(==1)
recieve an array of bits
return number of bitst turned on
time O(1)
space O(1)
*/
size_t CountOn(bitarray_t data);

/*
CountOff
count number of bits that are turned off(==0)
recieve an array of bits
return number of bitst turned on
time O(1)
space O(1)
*/
size_t CountOff(bitarray_t data);

/*
ToString
convert the array to a string
recieve an array of bits and buffer
return a pointer to a string
time O(n)
space O(n)
*/
char *ToString(bitarray_t data, char *buffer);

/*
CountBits
count the number of bits 1 with a LUT
recieve an array of bits
return int the number of bits == 1
time O(1)
space O(1)
*/
int CountBits(bitarray_t data);

/*
MirrorLut
mirror an array of bits (10011 -> 11001) using LUT
recieve an array of bits
return array of bits
time O(1)
space O(1)
*/
bitarray_t MirrorLut(bitarray_t data);

#endif
