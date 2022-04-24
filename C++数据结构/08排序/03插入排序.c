#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<sys\timeb.h>

#define MAX 10

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

//插入排序
void InsertSort(int arr[], int len)
{
	int j;
	for (int i = 1; i < len; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			int temp = arr[i];//缓存当前位置的值

			//满足条件向前移动
			for (j = i - 1; j >= 0 && temp < arr[j]; j--)
			{
				//交换
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp; 
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
		int randNum = rand() % MAX;
		arr[i] = randNum;
	}

	PrintArray(arr, MAX);

	InsertSort(arr, MAX);
	PrintArray(arr, MAX);


	system("pause");
	return 0;
}