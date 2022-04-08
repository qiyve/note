#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define SIZE 5

int main01()
{
	//数组第一
	//int arr[5] = { 1,2,3,4,5 };
	//int arr[] = { 1,2,3,4,5 };
	//int arr[10] = { 0 };
	//int arr[10] = { 1 };//默认0补充
	int arr[10];
	arr[0] = 1;

	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		printf("%d\n", arr[i]);
	}

	system("pause");
	return 0;
}
int main02()
{
	//int i = 10;
	//数据元素必须是常量 或常量表达式
	//int arr[i]; 错误
	//数组必须预先知道大小 动态数组 -》开辟空间
	int arr[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < SIZE; i++)
	{
		printf("%d\n", arr[i]);
	}

	system("pause");
	return 0;
}
int main()
{
	int arr[5] = { 1,2,3,4,5};

	//下标越界 运行时异常 
	printf("%d\n", arr[-1]);
	printf("%d\n", arr[5]);
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", arr[i]);
	}

	return 0;

}