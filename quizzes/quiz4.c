
#include <stdio.h>/* strlen strcpy */

typedef struct return_index
{
  int ret;
  int i1;
  int i2;
} return_index;

return_index IsSumFound(int sort_arr[], int sum, int size);

int main(void)
{
	int arr[] = {2, 4, 7, 12, 14};
	int sum = 20;
	int size = (sizeof(arr) / sizeof(int));
	return_index r = IsSumFound(arr, sum, size);
	
	printf("return: %d \nindex1: %d \nindex2: %d\n",r.ret,r.i1,r.i2);
	return 0;	
}

return_index IsSumFound(int sort_arr[], int sum, int size)
{
	return_index r_i = {0, 0, 0};
	int start = 0;
	int end = size - 1;
	
	while (start < end)
	{
		if (sort_arr[start] + sort_arr[end] == sum)
		{
			r_i.ret = 1;
			r_i.i1 = start;
			r_i.i2 = end;
			return r_i;
		}
		else if (sort_arr[start] + sort_arr[end] > sum)
		{
			--end;
		}
		else
		{
			++start;
		}
	}
	
	return r_i;
}
