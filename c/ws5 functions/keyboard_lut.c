#include <stdio.h> /* printf getchar*/
#include <stdlib.h> /* system */

void print_a();
void print_t();
void escape();
void empty();

#define SIZE  256

static int FLAG = 1;
typedef void (*func)();

int main(void)
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

	return 0;
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


