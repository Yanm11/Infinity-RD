#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"

void *MemSet(void *s, int c, size_t n)
{
	size_t size_word = sizeof(size_t);
	size_t *ptr = (size_t*)s;
	unsigned char *ptr2 = (unsigned char*)s;
	size_t char_value = (unsigned char)c;
	
	while (n > 0)
	{
		/* check if allined */
		if (((size_t)ptr % size_word) == 0 && n > size_word)
		{
			/* making sure the charcter is in the right size */
			size_t i = 1;
			for (; i < size_word; ++i) 
			{
				char_value = char_value * 256 + (unsigned char)c;		
			}
			
			/* assigning the value at size word until n is smaller */
			while (n > size_word)
			{
				*ptr = char_value;
				++ptr;
				n -= size_word;
			}
			
			ptr2 = (unsigned char*)ptr; /* ptr2 must point to where ptr points */
		}
		
		/* if there are remaining bytes or the str is not aligned */
		else
		{
			*ptr2 = c;
			++ptr2;
			--n;
			
			ptr = (size_t*)ptr2; /* ptr must point now to where ptr2 has changed */
		}
	}
	
	return s;
}

void *MemCpy(void *dest, const void *src, size_t n)
{
	size_t size_word = sizeof(size_t);
	
	size_t *ptr_dest1 = (size_t*)dest;
	unsigned char *ptr_dest2 = (unsigned char*)dest;
	
	size_t *ptr_src1 = (size_t*)src;
	unsigned char *ptr_src2 = (unsigned char*)src;
	
	while (n > 0)
	{
		/* check if allined */
		if (((size_t)ptr_dest1 % size_word) == 0 &&
			 ((size_t)ptr_src1 % size_word) == 0 &&
			  n > size_word)
		{
			/* assigning the value at size word until n is smaller */
			while (n > size_word)
			{
				*ptr_dest1 = *ptr_src1;
				++ptr_dest1;
				n -= size_word;
				++ptr_src1;
			}
			
			/* update the other ptr */
			ptr_src2 = (unsigned char*)ptr_src1;	
			ptr_dest2 = (unsigned char*)ptr_dest1; 
		}
		
		/* if there are remaining bytes or the str is not aligned */
		else
		{
			*ptr_dest2 = *ptr_src2;
			++ptr_dest2;
			++ptr_src2;
			--n;
			
			/* update the other ptr */
			ptr_src1 = (size_t*)ptr_src2;	
			ptr_dest1 = (size_t*)ptr_dest2; 
		}
	}
	return dest;
}

void *MemMove(void *dest, const void *src, size_t n)
{
	size_t size_src = strlen(src) + 1;
	size_t diff_dest_src = (size_t)dest - (size_t)src;
	
	/* if overlapping */
	if (diff_dest_src > 0 && diff_dest_src < size_src)
	{
		size_t size_word = sizeof(size_t);
	
		size_t *ptr_dest1 = (size_t*)dest + n;
		unsigned char *ptr_dest2 = (unsigned char*)dest + n;
		
		size_t *ptr_src1 = (size_t*)src + n;
		unsigned char *ptr_src2 = (unsigned char*)src + n;
		
		while (n > 0)
		{
			/* check if allined */
			if (((size_t)ptr_dest1 % size_word) == 0 &&
			 	((size_t)ptr_src1 % size_word) == 0 &&
			  	n > size_word)
			{
				/* assigning the value at size word until n is smaller */
				while (n > size_word)
				{
					--ptr_src1;
					--ptr_dest1;
					*ptr_dest1 = *ptr_src1;
					n -= size_word;
				}
			
				/* update the other ptr */
				ptr_src2 = (unsigned char*)ptr_src1;	
				ptr_dest2 = (unsigned char*)ptr_dest1; 
			}
		
			/* if there are remaining bytes or the str is not aligned */
			else
			{
				--ptr_src2;
				--ptr_dest2;
				*ptr_dest2 = *ptr_src2;
				--n;
			
				/* update the other ptr */
				ptr_src1 = (size_t*)ptr_src2;	
				ptr_dest1 = (size_t*)ptr_dest2; 
			}
		}
		return dest;
	}
	else
	{
		return MemCpy(dest, src, n);
	}
}






















