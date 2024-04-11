#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */





int main(void)
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
	
	return 0;
}


