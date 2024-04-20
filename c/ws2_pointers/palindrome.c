#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int palindrome(char *str);

int main()
{
	char str[] = "1234!!4321";
	
	if (palindrome(str))
	{
		printf("succsess! its palindrome\n");
	}
	else
	{
		printf("not palindrome\n");
	}
	
	return 0;





}

int palindrome(char *str)
{
	char *start = str;
	char * end = str + strlen(str) - 1;
	
	while (*start)
	{
		if	(*start == *end)
		{
			++start, --end;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
