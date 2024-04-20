#include <stdio.h> /* printf getchar*/
#include <stdlib.h> /* system */


int main(void)
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
	
	return 0;
}


