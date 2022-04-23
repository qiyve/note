#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<sys\timeb.h>

#define MAX 2000

//记录时间
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


//冒泡排序改进版
int flag = 0; //0 标识  没有排序好
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

//选择排序
void SelectSrot(int arr[], int len)
{

	//选择排序是以减少交换次数提升效率
	for (int i = 0; i < len; i++)
	{
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			//获取最小值下标
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}

		if (min != i)
		{
			Swap(&arr[min], &arr[i]);
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
	int arr2[MAX];
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX; i++)
	{
		int randNum = rand() % MAX;
		arr[i] = randNum;
		arr2[i] = randNum;
	}

	//选择排序测试
	//PrintArray(arr, MAX);
	//SelectSrot(arr, MAX);
	//PrintArray(arr, MAX);

	//冒牌排序
	long tbubble_start = getSystemTime();
	BubbleSort(arr, MAX);
	long tbubble_end = getSystemTime();
	printf("冒牌排序%d个元素，所需时间：%1d\n", MAX, tbubble_end - tbubble_start);
	
	//选择排序
	long tselect_start = getSystemTime();
	SelectSrot(arr2, MAX);
	long tselect_end = getSystemTime();
	printf("冒牌排序%d个元素，所需时间：%1d\n", MAX, tselect_end - tselect_start);

	system("pause");
	return 0;
}