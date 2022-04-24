#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<sys\timeb.h>

#define MAX 30000

//记录时间
long getSystemTime()
{
	struct timeb tb;
	ftime(&tb);
	
	return tb.time * 1000 + tb.millitm;
}

//希尔排序  从小到大
void ShellSort(int arr[], int len)
{
	//创建
	int increasement = len;
	int i, j, k;
	do
	{
		//确定分组增量
		increasement = increasement / 3 + 1;
		
		//确定每一组的第一个元素
		for (i = 0; i < increasement; i++)
		{
			//遍历当前一组
			for (j = i + increasement; j < len; j += increasement)
			{
				if (arr[j] < arr[j - increasement])
				{
					int temp = arr[j]; //缓存 
					for (k = j - increasement; k >= 0 && temp < arr[k]; k -= increasement)
					{
						arr[k + increasement] = arr[k]; //移动
					}
					arr[k + increasement] = temp;//插入

				}
			}
		}
	} while (increasement > 1);

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
				//移动
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
	int arr2[MAX];
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX; i++)
	{
		int randNum = rand() % MAX;
		arr[i] = randNum;
		arr2[i] = randNum;
	}

	//PrintArray(arr, MAX);
	//ShellSort(arr, MAX);
	//PrintArray(arr, MAX);

	//希尔排序和插入排序所需时间
	long tshell_start = getSystemTime();
	ShellSort(arr, MAX);
	long tshell_end = getSystemTime();
	printf("希尔排序%d个元素，所需时间：%d\n", MAX, tshell_end - tshell_start);

	long tinsert_start = getSystemTime();
	InsertSort(arr2, MAX);
	long tinsert_end = getSystemTime();
	printf("插入排序%d个元素，所需时间：%d\n", MAX, tinsert_end - tinsert_start);



	system("pause");
	return 0;
}