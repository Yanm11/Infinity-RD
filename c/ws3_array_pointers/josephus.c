#include <stdio.h> /* printf scanf */

static int Josephus(int n);

int main(void)
{
	int n;
	
	printf("number of soldiers: ");
	scanf("%d", &n);
	
	printf("the soldier left standing is at index: %d \n", Josephus(n));
	
	return 0;	
}

int Josephus(int n)
{
	int i = 0;
	int step = 2;
	int next_kill = 0;
	int sum = n;
	int first_alive = 0;
	int new_round = 0;
	
	while (sum != 1)
	{
		next_kill = i + step / 2;
		new_round = 0;
		
		
		if (i >= n)
		{
			i = first_alive;
			step *= 2;
			next_kill = i + step / 2;
		}
		
		else if (next_kill >= n)
		{
			next_kill = first_alive;
			i = first_alive + step;
			step *= 2;
			new_round = 1;
			first_alive = i;
		}
		
		sum -= 1;
		
		if (!new_round)
		{
			i += step;
		}
	
	}
	
	return first_alive;
}











