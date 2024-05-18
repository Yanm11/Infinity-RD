#include <stdio.h> /* printf getchar*/
#include <stdlib.h> /* system */

#include "ws4.h"

static int FLAG = 1;

#define SIZE  256

void Keyboard()
{
	char c = 0;
	int esc = 27;
	system ("stty -icanon -echo");
	printf("Start writing\n");
	
	while( c != esc)
	{
		c = getchar();
		
		if (c == 'a' || c == 'A')
		{
			printf("A-pressed\n");
		}
		
		else if (c == 't' || c == 'T')
		{
			printf("T-pressed\n");
		}
	}


	system ("stty icanon echo");

}

void print_a()
{
	printf("a-pressed\n");
}


void print_t()
{
	printf("t-pressed\n");
}


void escape()
{
	FLAG = 0;
}


void empty()
{
	
}
void KeyBoardLut()
{
	func arr_func[256];
	int i = 0;
	int c = 0;
	
	system ("stty -icanon -echo");
	printf("Start writing\n");
	
	for (; i < SIZE; i++)
	{
		if (i == 27)
		{
			arr_func[i] = escape;
		}
		else if (i == 97)
		{
			arr_func[i] = print_a;
		}
		else if (i == 116)
		{
			arr_func[i] = print_t;
		}
		else
		{
			arr_func[i] = empty;
		}
	}
	
	while(FLAG)
	{
		c = getchar();
		arr_func[c]();
	}
	
	system ("stty icanon echo");
}

void KeyBoardSwitch()
{
	char c = 0;
	int esc = 27;
	system ("stty -icanon -echo");
	printf("Start writing\n");
	
	while( c != esc)
	{
		c = getchar();
		
		switch (c)
		{
			case 'A':
			printf("A-pressed\n");
			break;
			
			case 'a':
			printf("a-pressed\n");
			break;
			
			case 'T':
			printf("T-pressed\n");
			break;
			
			case 't':
			printf("t-pressed\n");
			break;
			
		}
	}
	
	system ("stty icanon echo");
	
}
