#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ws3.h"

#define ROWS 4
#define COLS 4

void func(int array[ROWS][COLS], int arr[])
{
  int i, j;
  printf("[");
  for (i=0; i<ROWS; i++)
  {
    for (j=0; j<COLS; j++)
    {
      array[i][j] = i*j;
      arr[i] = arr[i] + array[i][j];
      printf(",%d ", array[i][j]);
    }
    printf("\n");
    
  }
  printf("]\n");
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

void Memory(char **buffer, int num_env_var)
{
	int i = 0;
	for(; i < num_env_var ; i++)
	{
		buffer[i] = (char *)malloc((strlen(environ[i])+1) * sizeof(char));
	
		if (buffer[i] == NULL)
		{
			--i;
			for (; i > 0; i--)
			{
				free(buffer[i]);
			}
			free(buffer);
		}
	}
}


void ToLower(char *str)
{
	char *ptr = str;
	
	while (*ptr)
	{
		*ptr = tolower(*ptr);
		++ptr;
	}
}
