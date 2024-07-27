#include <string.h> /* strlen */
#include <stdio.h> /* printf */
#include <assert.h> /* assert*/ 
#include <stddef.h> /* size_t */

char *ReverseWordsInSentence(char *str);
char *ReverseNBytes(char *str, size_t n);
size_t StrLenByDelim(char *str, char delim);

int main(void)
{
	char str[] = "12345 6789 hello";
	
	printf("reverse of str is: %s\n", ReverseWordsInSentence(str));
	
	return 0;
}

char *ReverseWordsInSentence(char *str)
{
	char *new = NULL;
	size_t bytes_in_word = 0;
	char delim = ' ';
	
	assert(str);

	new = ReverseNBytes(str, strlen(str));
	
	while ('\0' != *new)
	{
		bytes_in_word = StrLenByDelim(new, delim);
		ReverseNBytes(new, bytes_in_word);
		new += bytes_in_word + 1; 
	}	
	
	return str;
}

char *ReverseNBytes(char *str, size_t n)
{
	char *end = str + n - 1;
	char *start = str;
	
	assert(str);
	
	while (start < end)
	{
		char tmp = *start;
		*start = *end;
		*end = tmp;
		
		++start;
		--end;
	}
	
	return str;
}

size_t StrLenByDelim(char *str, char delim)
{
	size_t counter = 0;
	
	while (delim != *str && '\0' != *str)
	{
		++counter;
		++str;
	}
	
	return counter;
}
