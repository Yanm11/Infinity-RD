
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
	char str[] = "hello";
	char *str1 = str;
	int str1_len = strlen(str1) + 1;
	char *str2 = (char *)malloc(str1_len * sizeof(char));
	char *str3 = (char*)malloc(str1_len * sizeof(char));
	
	while (*str1)
	{
		*str3 = *str1;
		++str3;
		++str1;
	}
	
	str1 -= (str1_len - 1);
	str3 -= (str1_len - 1);
	strcpy(str2, str1);
	
	if(islower(*str1))
	{
		*str1 = toupper (*str1) ;
	}

	free(str2);
	free(str3);
	return 0;
}
