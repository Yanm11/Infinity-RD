#include <stdio.h>

void bursa(int arr[] ,int pro[], size_t size);

int main(void)
{
	int arr[] = {6,12,3,5,1,4,7,2};
	int pro[] = {0 , 0 , 0};
	bursa(arr, pro, 8);
	printf("%d %d %d \n" ,pro[0] , pro[1] , pro[2]);
return 0;
}

void bursa(int arr[] ,int pro[], size_t size)
{
	size_t i = 0;
	int min = arr[0];
	int max = arr[0];
	int buy_i = 0;
	int sell_i = 0;
	
	for(; i < size ; i++)
	{
		if(arr[i] < min)
		{
			min = arr[i];
			buy_i = i;
		}
		else if(arr[i] > max || arr[i] - min > pro[2])
		{
			max = arr[i];
			sell_i = i;
		}
		
		if (buy_i < sell_i)
		{
			pro[0] = buy_i;
			pro[1] = sell_i;
			pro[2] = max - min;
		}
	}
}
