#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void RmEdg(char *str); 
void WhiteSpace(char *str);

int main()
{
	/*char *str = (char *)malloc(1000);*/
	/*char *s1 = (char*)malloc(100);*/
	char s1[]= " hello       world            !      k   ";
	
	printf("old string: %s\n", s1);
	RmEdg(s1);
	
	printf("new string: %s\n", s1);
	printf("new string: hello world!\n");
	return 0;
}

void RmEdg(char *str) 
{
   
    char *ptr = str;
    while (*ptr && isspace(*ptr))
    {
        ptr++;
    }
    memmove(str, ptr, strlen(ptr) + 1); 
    
    
    ptr = str + strlen(str) - 1;
    while (ptr >= str && isspace(*ptr))
    {
        *ptr = '\0';
        ptr--;
    }
    
    WhiteSpace(str);
}


void WhiteSpace(char *str)
{
	char *ptr = str;
	char *space;
	
	while (*ptr)
	{	
		if (isspace(*ptr) && (isspace(*(ptr + 1)) || isspace(*(ptr-1))))
		{
			space = ptr;
			while (*space)
			{
				*space = *(space + 1);
				++space;
			}
			continue;
		}
		
		++ptr;
	}
}








