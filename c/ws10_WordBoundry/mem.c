#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"

#define SIZE_WORD  (sizeof(size_t))

void *MemSet(void *s, int c, size_t n)
{
	
	size_t *ptr_word = (size_t*)s;
	unsigned char *ptr_char = (unsigned char*)s;
	size_t char_value = (unsigned char)c;
	
	while (n > 0)
	{
		/* check if allined */
		if (((size_t)ptr_word % SIZE_WORD) == 0 && n > SIZE_WORD)
		{
			/* making sure the charcter is in the right size */
			size_t i = 1;
			for (; i < SIZE_WORD; ++i) 
			{
				char_value = char_value * 256 + (unsigned char)c;		
			}
			
			/* assigning the value at size word until n is smaller */
			while (n > SIZE_WORD)
			{
				*ptr_word = char_value;
				++ptr_word;
				n -= SIZE_WORD;
			}
			
			ptr_char = (unsigned char*)ptr_word; /* update the other ptr */
		}
		
		/* if there are remaining bytes or the str is not aligned */
		else
		{
			*ptr_char = c;
			++ptr_char;
			--n;
			
			ptr_word = (size_t*)ptr_char; /* update the other ptr */
		}
	}
	
	return s;
}

void *MemCpy(void *dest, const void *src, size_t n)
{
	size_t *ptr_dest_word = (size_t*)dest;
	unsigned char *ptr_dest_char = (unsigned char*)dest;
	
	size_t *ptr_src_word = (size_t*)src;
	unsigned char *ptr_src_char = (unsigned char*)src;
	
	while (n > 0)
	{
		/* check if allined */
		if (((size_t)ptr_dest_word % SIZE_WORD) == 0 &&
			 ((size_t)ptr_src_word % SIZE_WORD) == 0 &&
			  n > SIZE_WORD)
		{
			/* assigning the value at size word until n is smaller */
			while (n > SIZE_WORD)
			{
				*ptr_dest_word = *ptr_src_word;
				++ptr_dest_word;
				++ptr_src_word;
				n -= SIZE_WORD;
			}
			
			/* update the other ptr */
			ptr_src_char = (unsigned char*)ptr_src_word;	
			ptr_dest_char = (unsigned char*)ptr_dest_word; 
		}
		
		/* if there are remaining bytes or the str is not aligned */
		else
		{
			*ptr_dest_char = *ptr_src_char;
			++ptr_dest_char;
			++ptr_src_char;
			--n;
			
			/* update the other ptr */
			ptr_src_word = (size_t*)ptr_src_char;	
			ptr_dest_word = (size_t*)ptr_dest_char; 
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
		size_t *ptr_dest_word = (size_t*)dest + n;
		unsigned char *ptr_dest_char = (unsigned char*)dest + n;
		
		size_t *ptr_src_word = (size_t*)src + n;
		unsigned char *ptr_src_char = (unsigned char*)src + n;
		
		while (n > 0)
		{
			/* check if allined */
			if (((size_t)ptr_dest_word % SIZE_WORD) == 0 &&
			 	((size_t)ptr_src_word % SIZE_WORD) == 0 &&
			  	n > SIZE_WORD)
			{
				/* assigning the value at size word until n is smaller */
				while (n > SIZE_WORD)
				{
					--ptr_src_word;
					--ptr_dest_word;
					*ptr_dest_word = *ptr_src_word;
					n -= SIZE_WORD;
				}
			
				/* update the other ptr */
				ptr_src_char = (unsigned char*)ptr_src_word;	
				ptr_dest_char = (unsigned char*)ptr_dest_word; 
			}
		
			/* if there are remaining bytes or the str is not aligned */
			else
			{
				--ptr_src_char;
				--ptr_dest_char;
				*ptr_dest_char = *ptr_src_char;
				--n;
			
				/* update the other ptr */
				ptr_src_word = (size_t*)ptr_src_char;	
				ptr_dest_word = (size_t*)ptr_dest_char; 
			}
		}
		return dest;
	}
	else
	{
		return MemCpy(dest, src, n);
	}
}






















