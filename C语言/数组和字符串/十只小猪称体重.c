#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define SIZE 10
int main()
{
	//十只小猪称体重
	//创建数组
	int arr[SIZE];
	
	//获取小猪体重
	for (int i = 0; i < SIZE; i++)
	{
		scanf("%d", &arr[i]);
	}
	
	//比较体重 创建一个最大值变量
	//int max = 0; 
	int max = arr[0];

	for (int i = 1; i < SIZE; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	printf("最重的小猪体重为：%d\n", max);

	return 0;

}