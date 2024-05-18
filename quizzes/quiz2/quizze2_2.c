#include <stdio.h> /* printf */
#include <string.h> /* strlen */
#include <ctype.h> /* tolower */

char *Reverse(char *str);

int main(void)
{
	char str[] = "HELLO worLD";
	Reverse(str);
	
	printf("str: %s \n", str);
	
	return 0;
}

char *Reverse(char *str)
{
	char *start = str;
	char *end = str + strlen(str) - 1;
	char tmp = 'a';
	
	while (end != start - 2 && end != start - 1)
	{
		tmp = *start;
		*start = tolower(*end);
		*end = tolower(tmp);
		
		++start, --end;
	}
	return (str);
}
