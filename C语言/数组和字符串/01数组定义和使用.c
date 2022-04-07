#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main01()
{
	//变量定义
	//数据类型 变量  = 值
	//数组定义
	//数据类型 数组名[元素个数] = {值1，值2，值3}
	int arr[10] = { 9,5,8,7,6,1,4,2,3,10 };

	//数组下标 从0开始  数组名[下标]
	//数组下标是从0开始的到数组元素个数 - 1	
	//printf("%d\n", arr[0]);
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", arr[i]);
	}

	system("pause");
	return 0;
}
int main02()
{
	//数据元素参与计算
	int arr[5] = { 1,2,3,4,5, };
	arr[0] = arr[4];
	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", arr[i]);
	}
	
	return 0;
}

int main()
{
	 //数组在内存中存储方式和大小
	int arr[5] = { 1,2,3,4,5 };

	//下标为0的元素地址 地址用 %p
	printf("%p\n", &arr[0]);
	//printf("%p\n", &arr[1]); 
	//printf("%p\n", &arr[2]);
	//printf("%p\n", &arr[3]);
	//printf("%p\n", &arr[4]);

	//数组名是一个地址常量 指向数组首地址的常量
	printf("%p\n", arr);

	//大小 数据在内存中占的大小 = 数组类型 * 元素个数
	printf("数据在内存中占的大小：%d\n", sizeof(arr));
	printf("数据元素大小：%d\n", sizeof(arr[0]));
	printf("数据元素个数：%d\n", sizeof(arr) / sizeof(arr[0]));

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d\n", arr[i]);
	}

	return 0;
}