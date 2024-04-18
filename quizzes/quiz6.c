#include <stdio.h>
#include <string.h>

int Rotation(char *s1, char *s2);

int main()
{
	char s1[] = "123456";
	char s2[] = "652134";
	
	if (Rotation(s1,s2))
	{
		printf("s2 IS a rotation of s1\n");
	}
	else
	{
		printf("s2 is NOT a rotation of s1\n");
	}
	
	return 0;
}


int Rotation(char *s1, char *s2)
{
	size_t len_s1 = strlen(s1);
	size_t len_s2 = strlen(s2);
	
	if (len_s1 != len_s2)
	{
		return 0;
	}
	
	return (strspn(s1,s2) == len_s1);
}
