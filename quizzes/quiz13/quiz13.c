#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define SIZE_WORD (sizeof(size_t))

void *MemCpy(void *dest, const void *src, size_t n)
{
	size_t *ptr_dest_word = NULL;
	unsigned char *ptr_dest_char = NULL;
	
	size_t *ptr_src_word = NULL;
	unsigned char *ptr_src_char = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	ptr_dest_word = (size_t*)dest;
	ptr_dest_char = (unsigned char*)dest;
	
	ptr_src_word = (size_t*)src;
	ptr_src_char = (unsigned char*)src;
	
	while (n > 0)
	{
		/* check if allined */
		if ((((size_t)ptr_dest_word % SIZE_WORD) == 0) &&
			 (((size_t)ptr_src_word % SIZE_WORD) == 0) &&
			  (n > SIZE_WORD))
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

int TestMemCpy(char *str1, char *str2)
{
	if (strcmp(str1, str2) == 0)
	{
		printf("memcpy test PASSED\n");
		return 0;
	}
	
	else
	{
		printf("memcpy test FAILED\n");
		return -1;
	}
}

int main(void)
{	
	/* set the str to test memcpy */
	char *str_cpy1 = NULL;
	char *str_cpy2 = NULL;
	char *str_cpy3 = "helloworldworldhello";
	
	/* set the str to test memcpy */	
	str_cpy1 = (char *)calloc(21,1);
	str_cpy2 = (char *)calloc(21,1);
	strcpy(str_cpy1, "hello");
	strcpy(str_cpy2, "hello");
	
	TestMemCpy(MemCpy(str_cpy1,str_cpy3,14),memcpy(str_cpy2,str_cpy3,14));


	
	return 0;
}
