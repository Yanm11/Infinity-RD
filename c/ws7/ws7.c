#include <stdio.h>

typedef unsigned int u_int;

long Pow2(unsigned int x, unsigned int y);
int CheckPow2loop(u_int n);
int CheckPow2(u_int n);
int AddOne(int n);
int ThreeBitsOn(u_int n[], int size);
int ByteMirrorLoop(unsigned char c);
int  ByteMirror(unsigned char c);
int CheckNoIf1(unsigned char n);
int CheckNoIf2(unsigned char n);
int CheckNoIf3(unsigned char n);
int Div16(u_int n);
int Swap(u_int *n1, u_int *n2);
int CountBitsLoop(int n);
int CountBits(int n);
int FloatPrint();

int main(void)
{
	u_int n[] = {7, 8, 10, 11, 13, 15};
	u_int x = 15;
	u_int *n1 = &x;
	u_int y = 20;
	u_int *n2 = &y;
	
	/* test 1 */
	Pow2(20,5);
	/* test 2.1 */
	printf("%d\n",CheckPow2loop(2147483648));
	/* test 2.2 */
	printf("%d\n",CheckPow2(2147483648));
	/* test 3 */
	printf("%d -> %d\n", 1234, AddOne(1234));
	/* test 4 */
	ThreeBitsOn(n,6);
	/* test 5 */
	ByteMirrorLoop(3);
	/* test 5.2 */
	ByteMirror(3);
	/* test 6.1 */
	printf("%d\n", CheckNoIf1(34));
	/* test 6.2 */
	printf("%d\n", CheckNoIf2(34));
	/* test 6.3 */
	printf("%d\n", CheckNoIf3(211));	
	/* test 7 */
	printf("%d\n", Div16(49));
	/* test 8 */
	Swap(n1,n2);
	printf("%d %d\n",x,y);
	/* test 9.1 */
	printf("%d\n",CountBitsLoop(65535));
	/* test 9.2 */
	printf("%d\n",CountBits(65535));
	/* test 10 */
	FloatPrint();

	return 0;
}




long Pow2(unsigned int x, unsigned int y)
{
	printf("%d x 2 ^ %d  =",x,y);
	
	x = x << y;	

	printf("%d\n", x);
	
	return x;
}

int CheckPow2loop(u_int n)
{
	/* using loop */
    u_int counter = 0;
 	int i = 0;
 	
    for (; i < 32; i++)
    {
        if (n & (1 << i))
        {
        	++counter;
        }
    }
    
    return (counter == 1);
}

int CheckPow2(u_int n)	
{
	/* using bitwis */
	if (n == 0)
	{
		return 0;
	}
		
	return ((n & (n - 1)) == 0);	
}

int AddOne(int n)
{
	return -(~n);
}

int ThreeBitsOn(u_int n[], int size)
{
	int i = 0;
	int j = 0;
	int count = 0;
	
	for (;i < size; i++)
	{
		for (j = 0;j < 32; j++)
		{
			if (n[i] & (1 << j))
			{
				++count;
			}
		}
		
		if (count == 3)
		{
			printf("exactly 3 bit on index %d for %d\n", i, n[i]);
		}
		
		count = 0;
	}
	return 1;
}

int ByteMirrorLoop(unsigned char c)
{
	unsigned char c_mirror = 0;
	int i = 0;
	
	for (;i < 8; i++)
	{
		c_mirror <<= 1;
		if (c & (1 << i))
		{ 
			c_mirror |= 1;
		}
	}
	printf("c: %d and c_mirror: %d \n", c, c_mirror);
	return 1;
}

int  ByteMirror(unsigned char c) 
{
	unsigned char c_mirror = 0;
   c_mirror = (c & 0xF0) >> 4 | (c & 0x0F) << 4;
   c_mirror= (c_mirror & 0xCC) >> 2 | (c_mirror & 0x33) << 2;
   c_mirror = (c_mirror & 0xAA) >> 1 | (c_mirror & 0x55) << 1;
   
   printf("c: %d and c_mirror: %d \n", c, c_mirror);
   return 1;
}

int CheckNoIf1(unsigned char n)
{
	return (n & (1 << 1) && (n & (1 << 5)));
}

int CheckNoIf2(unsigned char n)
{
	return (n & (1 << 1) || (n & (1 << 5)));
}

int CheckNoIf3(unsigned char n)
{
	unsigned char bit_3 = (n & 0x04) << 2;
	unsigned char bit_5 = (n & 0x10) >> 2;
	n = n & 0xEB;
	n = n | bit_5;
	n = n | bit_3;
	return n;
}

int Div16(u_int n)
{
	return (n & 0xF0);
}

int Swap(u_int *n1, u_int *n2)
{
	if (n1 == n2)
	{
		return 0;
	}
	*n1 = *n1 ^ *n2;
	*n2 = *n1 ^ *n2;
	*n1 = *n1 ^ *n2;
	return 1;
}



int CountBitsLoop(int n)
{
	int i = 0;
	int count = 0;
	
	for (;i < 32; i++)
	{
		if (n & (1 << i))
		{
			++count;
		}
	}
	return count;
}



int CountBits(int n)
{
	int BitsSetTable256[256];
	int i = 0;
	
    BitsSetTable256[0] = 0; 
    for (; i < 256; i++)
    { 
        BitsSetTable256[i] = (i & 1) + BitsSetTable256[i / 2]; 
    } 
	return (BitsSetTable256[n & 0xff] + 
            BitsSetTable256[(n >> 8) & 0xff] + 
            BitsSetTable256[(n >> 16) & 0xff] + 
            BitsSetTable256[n >> 24]); 
}

int FloatPrint()
{
    double f = 0.0;
	unsigned long *float_as_int = (unsigned long *)&f;
	int i;
	
	scanf("%lf",&f);

	for (i=0; i<=31; i++)
	{
		if (i==1)
		printf(" "); 
		if (i==5)
		printf(" "); 

		if ((*float_as_int >> (31-i)) & 1)
		printf("1");
		else
		printf("0");
	}
	printf("\n");
	return 1;
}












