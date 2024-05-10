#include <stdio.h> /* printf */
#include <stdlib.h> /* size_t */
#include <string.h> /* size_t */

int Flip(int num);
unsigned char Mirror(unsigned char c);
int FlipBit(int val, unsigned int n);
int CountBitOn(unsigned char c);
char RotateLeft(char byte, unsigned int nbits);
void SwapPtr(int **ptr1, int **ptr2);
size_t StrLen(const char *str);
int StrCmp(const char *str1, const char *str2);
char *StrNcpy(char *dest, const char *src, size_t n);
char *StrCpy(char *dest, const char *src);
char *StrCat(char *dest, const char *src);
unsigned long GetNFibonacciElement(unsigned int n);
char *IntToString(int num, char *str);
unsigned long Multiply8(unsigned long num);
void Swap1(int *ptr1, int *ptr2);
void Swap2(int *ptr1, int *ptr2);
void Swap3(int *ptr1, int *ptr2);
void foo1();
void foo2();

struct s1
{
	int *i;
	char c;
	short s;
	int *j;
};

/*struct s2
{
	unsigned int i:2;
	unsigned char c:1;
	unsigned short s:3;
	int *j;
	unsigned char x:2;
};
*/
union
{
	char arr[7];
	int i;
	short s;
} jack;
	
int main(void)
{
	/* variables */
	int num = -520;
	unsigned char c = 250;
	unsigned char c_mirror;
	int val = 15;
	int n = 2;
	unsigned int nbits = 3;
	int a = 5;
	int b = 6;
	int *p1 = &a;
	int *p2 = &b;
	char str1[] = "hello";
	char str2[] = "hello";
	char dest[] = "hello";
	char src[] = "hhhhh";
	char dest2[10] = "";
	char src2[] = "hello wor";
	char *dest3 = (char*)malloc(12);
	char src3[] = "world";
	unsigned int elem = 8;
	int numtostring = -12345;
	char num_str[7];
	unsigned long big_num = 123587989;
	int e = 5;
	int d = 6;
	int *c1 = &e;
	int *d2 = &d;
	
	/* q1 */
	printf("q1\n");
	printf("num: %d, fliped: %d\n", num, Flip(num));
	printf("-------------\n");
	
	/* q4 */
	printf("q4\n");
	c_mirror = Mirror(c);
	printf("c: %d, c mirror: %d\n",c,c_mirror);
	printf("-------------\n");
	
	/* q5 */
	printf("q5\n");
	printf("val: %d, new val: %d\n",val,FlipBit(val, n));
	printf("-------------\n");
	
	/* q6 */
	printf("q6\n");
	printf("number of bits on for %d is: %d\n",c, CountBitOn(c));
	printf("-------------\n");
	
	/* q8 */
	printf("q8\n");
	printf("number %d when shifted left by %d is: %d\n",c, nbits, RotateLeft(c, nbits));
	printf("-------------\n");

	/* q10 */
	SwapPtr(&p1, &p2);
	printf("q10\n");
	printf("%d,%d\n", a, b);
	printf("%d,%d\n", *p1, *p2);
	printf("-------------\n");
	
	/* q11 */
	printf("q11 strlen\n");
	printf("lentgh of %s is: %ld\n\n", str1, StrLen(str1));
	printf("q11 strcmp\n");
	printf("are %s and %s equal? %d\n\n", str1, str2, StrCmp(str1, str2));
	printf("q11 strncpy\n");
	printf("dest before copy: %s ", dest);
	printf("after %s\n\n", StrNcpy(dest, src, 4));
	printf("q11 strcpy\n");
	printf("dest before copy: %s ", dest2);
	printf("after %s\n\n", StrCpy(dest2, src2));
	printf("q11 strcat\n");
	StrCpy(dest3, "hello");
	printf("dest before cat: %s ", dest3);
	printf("after %s\n\n", StrCat(dest3, src3));
	printf("-------------\n");
	
	/* q12 */
	printf("q12\n");
	printf("element number %d in the fibo seris is:%lu\n\n", elem, GetNFibonacciElement(elem));
	printf("-------------\n");
	
	/* q13 */
	printf("q13\n");
	printf("int %d to string %s\n\n", numtostring, IntToString(numtostring, num_str));
	printf("-------------\n");
	
	/* q14 */
	printf("q14\n");
	printf("num %lu times 8 is:%lu\n\n", big_num, Multiply8(big_num));
	printf("-------------\n");
	
	/* q15 */
	printf("q15\n");
	Swap1(c1,d2);
	printf("e: %d, d: %d\n\n", e, d);
	Swap2(c1,d2);
	printf("e: %d, d: %d\n\n", e, d);
	Swap3(c1,d2);
	printf("e: %d, d: %d\n\n", e, d);
	printf("-------------\n");
	
	/* q16-17 */
	printf("q16-17\n");
	foo2();
	foo2();
	printf("-------------\n");
	
	/* q21-23 */
	printf("q21-23\n");
	/*printf("size of s1:%ld, size of s2: %ld, size of jack: %ld\n",sizeof(struct s1),sizeof(struct s2), sizeof(jack));*/
	jack.i = 30;
	printf("i: %d\n",jack.i);
	return 0;
}
/* q1 */
int Flip(int num)
{
	int flip_num = 0;
	int is_negative = (num < 0) ? -1 : 1;
	num = num * is_negative;
	
	while (num > 0)
	{
		flip_num *= 10;
		flip_num += num % 10;
		num /= 10;
	}
	 
	return  (is_negative * flip_num);
}

/* q4*/
unsigned char Mirror(unsigned char c) 
{
   c = (c & 0xF0) >> 4 | (c & 0x0F) << 4;
   c= (c & 0xCC) >> 2 | (c & 0x33) << 2;
   c = (c & 0xAA) >> 1 | (c & 0x55) << 1;
   
   return c;
}

/* q5 */
int FlipBit(int val, unsigned int n)
{
	val = val ^ (1 << n);
	return val;
}

/* q6 */
int CountBitOn(unsigned char c)
{
	int count = 0;
	while (c > 0)
	{
		c = c & (c - 1);
		++count; 
	}
	
	return count;
}

/* q8 */
char RotateLeft(char byte, unsigned int nbits)
{
	char mask = 0xFF;
	char tmp = 0;
	mask = ~(mask >> nbits);
	tmp = byte & mask;
	tmp = tmp >> (8 - nbits);
	byte = byte << nbits;
	byte = byte | tmp;
	
	return byte;
}

/* q10 */
void SwapPtr(int **ptr1, int **ptr2)
{
	int *tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

/* q11 */
size_t StrLen(const char *str)
{
	size_t count = 0;
	while ('\0' != *str)
	{
		++count;
		++str;
	}
	
	return count;
}

int StrCmp(const char *str1, const char *str2)
{
	
	while (('\0' != *str1) && ('\0' != *str2))
	{
		int diff = *str1 - *str2;
		
		if (0 != diff)
		{
			return diff;
		}
		++str1;
		++str2;
	}
	
	return *str1 - *str2;
}

char *StrNcpy(char *dest, const char *src, size_t n)
{
	char *start = dest;
	
	while (n > 0)
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	return start;
}

char *StrCpy(char *dest, const char *src)
{
	return StrNcpy(dest, src, StrLen(src));
}

char *StrCat(char *dest, const char *src)
{
	char *start = dest;
	
	dest = dest + StrLen(dest);
	
	StrCpy(dest, src);
	
	return start;
}

/* q12*/
unsigned long GetNFibonacciElement(unsigned int n)
{
	unsigned long fibo1 = 1;
	unsigned long fibo2 = 0;
	unsigned long fibo_tmp = 0;
	size_t i = 1;
	
	for (;i < n; ++i)
	{
		fibo_tmp = fibo1;
		fibo1 = fibo1 + fibo2;
		fibo2 = fibo_tmp;
	}
		
	return fibo1;
}

/* q13 */
char *IntToString(int num, char *str)
{
	sprintf(str,"%d",num);
	
	return str;
}

/* q14 */
unsigned long Multiply8(unsigned long num)
{
	return num << 3;
}

/* q15 */
void Swap1(int *ptr1, int *ptr2)
{
	int tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}


void Swap2(int *ptr1, int *ptr2)
{
	*ptr1 = *ptr1 + *ptr2;
	*ptr2 = *ptr1 - *ptr2;
	*ptr1 = *ptr1 - *ptr2;
}


void Swap3(int *ptr1, int *ptr2)
{
	*ptr1 = *ptr1^*ptr2;
	*ptr2 = *ptr1^*ptr2;
	*ptr1 = *ptr1^*ptr2;
}

/* q16 */
void foo1()
{
	char *s1 = "hello";
	char s2[] = "hello";
	char *s3 = s1;
	printf("%lu %lu %lu %lu \n",sizeof (s1), sizeof (s2) , strlen(s1), strlen (s2) );
	s3[0] = 'H';
	printf("%s \n", s3);
}

/* q17 */
void foo2()
{
	size_t array [] = {0, 1, 2, 3, 4, 5};
	size_t val = 3;
	printf("%lu \n", val[array]);
}

