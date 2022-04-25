#include<iostream>
using namespace std;
#include<time.h>
#include<sys/timeb.h>

#define MAX 50000

long getSystemTime()
{
	struct timeb tb;
	ftime(&tb);
	return tb.time * 1000 + tb.millitm;
}

//创建数组
int* CreateArray()
{
	srand((unsigned int)time(NULL));
	int* arr = (int*)malloc(sizeof(int) * MAX);
	
	for (int i = 0; i < MAX; i++)
	{
		arr[i] = rand() % MAX;
	}

	return arr;
}

//打印
void PrintArray(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i]<<" ";
	}
	cout << endl;
}
 
//合并算法  从小到大
void Merge(int arr[], int start, int end, int mid, int* temp)
{
	//创建辅助下边变量
	int i_start = start; //第一个有序序列开始
	int i_end = mid;  //结束

	int j_start = mid + 1; //第二 头
	int j_end = end;      //尾

	//表示辅助空间有多少个元素
	int len = 0;

	//合并两个有序序列
	while (i_start <= i_end && j_start <= j_end)
	{
		//比较i和j  并插入临时内存储
		if (arr[i_start] < arr[j_start])
		{
			//i的值小于 j的值
			temp[len] = arr[i_start];
			len++;   
			i_start++;
		}
		else
		{
			//i的值 >= j 
			temp[len] = arr[j_start];
			len++;
			j_start++;
		}
	}

	// 遍历序列中是否还有数据  
	//i序列
	while (i_start <= i_end)
	{
		temp[len] = arr[i_start];
		len++;
		i_start++;
	}
	// j序列
	while (j_start <= j_end)
	{
		temp[len] = arr[j_start];
		len++;
		j_start++;
	}

	//辅助空间数据覆盖原空间
	for (int i = 0; i < len; i++)
	{
		arr[start + i] = temp[i];
	}
}

//归并排序
void MergeSort(int arr[], int start, int end, int* temp)
{
	if (start >= end)
	{
		return;
	}

	int mid = (start + end) / 2;
	//分组
	//左半边
	MergeSort(arr, start, mid, temp);
	//右半边
	MergeSort(arr, mid + 1, end, temp);

	//合并
	Merge(arr, start, end, mid, temp);
}

int main()
{
	//创建数组
	int* arr = CreateArray();
	//辅助空间
	int* temp = (int*)malloc(sizeof(int) * MAX);

	//PrintArray(arr, MAX);
	long t_start = getSystemTime();
	MergeSort(arr, 0, MAX - 1, temp);
	long t_end = getSystemTime();
	//PrintArray(arr, MAX);
	printf("排序%d个元素，所取时间：%d\n", MAX, t_end - t_start);

	//释放空间
	free(temp);
	free(arr);

	system("pause");
	return 0;
}