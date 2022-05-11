#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void Select(int arr[],int len)
{
	int max = 0;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			if (arr[j] > arr[max])
			{
				max = j;
			}
		}
	}
    //最大值放到最后一位
	int temp = arr[len - 1];
	arr[len - 1] = arr[max];
	arr[max] = temp;
}

int main()
{
	int arr[] = { 100,5,6,8,9,200,7,8,5,2,1 };
	int len = sizeof(arr) / sizeof(arr[0]);

	Select(arr, len);
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	
	return 0;
}
