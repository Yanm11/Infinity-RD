#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

void millionChar(char c);

int main(void)
{
	char c = 'a';
	size_t i = 0;
	
	for (;i < 1000; ++i)
	{
		millionChar(c);
		if (i == 600)
		{
			millionChar('0');
		}
	}
	millionChar('0');
	
	return 0;
}

void millionChar(char c)
{
	static int char_lut[256] = {0};
	static int max = 0;
	
	++char_lut[c];
	max = (char_lut[c] > max) ? char_lut[c] : max;
	
	if (c == '0')
	{
		size_t i = 0;
		printf("max is %d\n", max);
		
		/* to reset the lut */
		for (;i < 256; ++i)
		{
			char_lut[i] = 0;
		}
		max = 0;
	}
}
