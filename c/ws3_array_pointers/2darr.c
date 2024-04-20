#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROWS 4
#define COLS 4

void func(int array[ROWS][COLS], int arr[]);

int main(void)
{
	
	int arr[ROWS][COLS];
	int *arr2 = (int *)malloc(ROWS * sizeof(int));
	
	
	func(arr,arr2);
	
	for (int i=0; i < ROWS; i++)
	{
		printf("%d, ",arr2[i]);
	}
	
	printf("\n");
	
	printf("sizeof array: %ld\n", sizeof(arr));
	free(arr2);
	return 0;
}



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


