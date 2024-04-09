#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

size_t StrSpn(const char *s, const char *accept);
char *StrStr(const char *haystack, const char *needle);
char *StrNcat(char *dest, const char *src, size_t n);
char *StrCat(char *dest, const char *src);
char *StrDup(const char *s);
char *StrChr(const char *s, int c);
int ToLower(int c);
int StrCaseCmp(const char *s1, const char *s2);
int StrNcmp(const char *s1, const char *s2, size_t n);
char *StrNcpy(char *dest, const char *src, size_t n);
char *StrCpy(char *dest, const char *src);
size_t StrLen(const char *s);
int StrCmp(const char *s1, const char *s2);

int main()
{
	/* Test for StrCpy and StrNcmp
	char s[] = "edewddkjih395ht95ht95ht9054hg950ghb590gb44628e";
	char *s2 = (char *) malloc(StrLen(s) * sizeof(char));
	
	s2 = strncpy(s2, s, 15);
	
	printf("copied string: %s\n", s2);
	free(s2);*/
	
	/* **************************************************************** */
	/* Test for StrNcmp StrCaseCmpr
	
	char s1[] = "ab";
	char s2[] = "ABCD";
	
	int x1 = StrCaseCmp(s1, s2);
	int x2 = strcasecmp(s1, s2); 
	
	printf("my code: %d, origin: %d\n", x1, x2);*/
	
	/* **************************************************************** */
	/* Test for StrChar 
	
	char s1[] = "aacbdtCtrbrctbrtbrtc";
	char c = 'c';
	
	char *s2 = strchr(s1,c);
	printf("the character for %c in %s is: %c\n", c,s1,*s2);*/
	
	/* **************************************************************** */
	/* Test for StrDup */
	
	char s[] = "hello";
	char *ptr_S = StrDup(s);
	
	printf("s: %s , duplicate s: %s\n", s, ptr_S);
	free(ptr_S);
	
	/* **************************************************************** */
	/* Test for Strcat and StrNcat
	
	char *s1 = (char*)malloc(100);
	StrCpy(s1,"ab");
	char s2[] = "cdgtrg";
	
	strncat(s1,s2,0);
	
	printf("new string: %s\n", s1);
	free(s1);*/
	/* **************************************************************** */
	/* Test for StrStr 
	
    char s1[] = "GeeksforGeeks";
    char s2[] = "GG";
    char* p;
 
    // Find first occurrence of s2 in s1
    p = StrStr(s1, s2);
 
    // Prints the result
    if (p) {
        printf("String found\n");
        printf("First occurrence of string '%s' in '%s' is "
               "'%s'",
               s2, s1, p);
    }
    else
        printf("String not found\n");
	
	
	/* Test for StrSpn 
	
	char s1[] = "hello";
	char s2[] = "eol";
	size_t i = StrSpn(s1,s2);
	printf("shows: %ld\n",i);*/
 


	
	
	
	
	return 0;
}




char *StrCpy(char *dest, const char *src)
{
	size_t i = 0;
	size_t j = 0;
	
	while (src[j])
	{
		dest[i] = src[j];
		++i, ++j;
	}
	return dest;
}


char *StrNcpy(char *dest, const char *src, size_t n)
{
	char *ptr1 = dest;
	const char *ptr2 = src;
	
	while (*ptr2 && n)
	{
		*ptr1 = *ptr2;
		++ptr1, ++ptr2, --n;
	}
	
	if (!*ptr2)
	{
		*ptr1 = '\0';
	}
	
	return dest;
}

int StrNcmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
	{
		return 0;
	}
	
	while (*s1 && *s2 && ((*s1-*s2) == 0) && n - 1)
	{
		++s1, ++s2, --n;
	}
	
	return (int)(*s1-*s2);
} 



int StrCaseCmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && ((ToLower(*s1)-ToLower(*s2)) == 0))
	{
		++s1, ++s2;
	}
	return (int)(ToLower(*s1)-ToLower(*s2));
}  


int ToLower(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return c;
	}
	else if (c >= 'A' && c <= 'Z')
	{
		return c + 32;
	}
}

char *StrChr(const char *s, int c)
{
	 char *ptr =(char*) s;
	
	while (*ptr)
	{
		if (*ptr == c)
		{
			return ptr;
		}
		
		++ptr;
	}
	
	return NULL;

}

char *StrDup(const char *s)
{
	char *ptr = (char *) malloc(StrLen(s) * sizeof(char) + 1);
	
	return StrCpy(ptr, s); 
}


char *StrCat(char *dest, const char *src)
{
	char *ptr1 = dest;
	const char *ptr2 = src;
	
	while (*ptr1)
	{
		++ptr1;
	}
	
	while (*ptr2)
	{
		*ptr1 = *ptr2;
		++ptr1,++ptr2;
	}
	*ptr1 = '\0';
	
	return dest;
}


char *StrNcat(char *dest, const char *src, size_t n)
{
	char *ptr1 = dest;
	const char *ptr2 = src;
	
	while (*ptr1)
	{
		++ptr1;
	}
	
	while (*ptr2 && n > 0)
	{
		*ptr1 = *ptr2;
		++ptr1, ++ptr2, --n;
	}
	*ptr1 = '\0';
	
	return dest;


}


char *StrStr(const char *haystack, const char *needle)
{
	char *ptr1 = (char *)haystack;
	const char *ptr2 = needle;
	
	size_t n = StrLen(needle);
	
	while (*ptr1)
	{
		if (*ptr2 == *ptr1 && !StrNcmp(ptr1,ptr2, n))
		{
			return ptr1;
		}
		++ptr1;
	}
	return NULL;
}


size_t StrSpn(const char *s, const char *accept)
{
	const char *ptr1 = s;
	const char *ptr2 = accept;
	size_t i = 0;
	
	while (*ptr1)
	{
		if (StrChr(ptr2, *ptr1))
		{
			++ptr1, ++i;	
		}
		else
		{
			return i;
		}
	}
	
	return i;

}




size_t StrLen(const char *s)
{
	size_t count = 0;
	const char *ptr = s;
	while (*ptr)
	{
		++count;
		++ptr;
	}

	return count; 
}


int StrCmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && ((*s1-*s2) == 0))
	{
		++s1, ++s2;
	}
	return (int)(*s1-*s2);
}  
