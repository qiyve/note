#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<sys\timeb.h>

#define MAX 10

//记录毫秒
long getSystemTime()
{
	struct timeb tb;
	ftime(&tb);
	
	return tb.time * 1000 + tb.millitm;
}

//交换
void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


int flag = 0; //0 标识  没有排序好
//冒泡排序
void BubbleSort(int arr[], int len)
{
	for (int i = 0; i < len && flag == 0; i++)
	{
		flag = 1; //认为已经排序号
		for (int j = 0; j < len -i -1 ; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				flag = 0;
				Swap(&arr[j], &arr[j + 1]);
			}
		}
		
	}
}

//打印
void PrintArray(int arr[],int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}


int main()
{
	int arr[MAX];
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX; i++)
	{
		arr[i] = rand() % MAX;

	}

	printf("排序前\n");
	PrintArray(arr, MAX);
	long t_start = getSystemTime();
	printf("排序后\n");
	BubbleSort(arr, MAX);
	long t_end = getSystemTime();
	printf("冒泡排序%d个元素，所需时间:%1d\n", MAX, t_end - t_start);
	PrintArray(arr, MAX);

	system("pause");
	return 0;
}