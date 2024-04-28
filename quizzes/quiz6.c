#include <stdio.h>
#include <string.h>

int Rotation(char *s1, char *s2);

int main()
{
	char s1[] = "123456";
	char s2[] = "234561";
	
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
	char *ptr_s1_start = s1;
	size_t len_s1 = strlen(s1);
	char tmp = 0;
	size_t i = 0;
	
	for (;i < len_s1; i++)
	{
		size_t j = 0;
		tmp = *s1;

		if (strcmp(s1,s2) == 0)
		{
			return 1;
		}
		
		for(;j < len_s1 - 1; j++)
		{
			*s1 = *(s1+1);
			++s1;
		}
		
		*s1 = tmp;
		s1 = ptr_s1_start;
	}
	
	return 0;
}
