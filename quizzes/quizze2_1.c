#include <stdio.h>

void TF(int num);

int main(void)
{
	int x = 16;
	TF(x);
	
	return 0;
}

void TF(int num)
{
	int i = 1;
	
	for (; i < num; i++)
	{
		if (i % 3 == 0 && i % 5 == 0)
		{
			printf("TF \n");
		}
		else if (i % 5 == 0)
		{
			printf("F \n");
		}
		else if ( i % 3 == 0)
		{
			printf("T \n");
		}
		else
		{
			printf("%d \n", i);
		}
	}
}
