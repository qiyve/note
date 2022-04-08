#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

//二维数组

int main01()
{
	//数据类型  数组名[行][列]
	// {
	//  {值1，值2}，
	//  {值3，值4}
	// }
	int arr[2][3] =
	{
		{1,2,3},
		{4,5,6}
	};

	//arr[1][2] = 20;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	printf("数组大小：%d\n", sizeof(arr));//行数 * 列数 * sizeof(数据类型）
	printf("数组一行大小：%d\n", sizeof(arr[0]));
	printf("数组元素大小：%d\n", sizeof(arr[0][0]));

	printf("数组行数：%d\n", sizeof(arr) / sizeof(arr[0]));
	printf("数组列数：%d\n", sizeof(arr[0]) / sizeof(arr[0][0]));


	system("pause");
	return 0;
}

int main02()
{
	int arr[2][3] =
	{
		{1,2,3},
		{4,5,6}
	};

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%p\n", &arr[i][j]);
		}

	}
	//二维数组首地址
	//printf("%p\n", arr);
	//printf("%p\n", arr[0]);
	////arr[0] = 100; 错误 这是一行数据
	//printf("%p\n", &arr[0][0]);
	//printf("%p\n", &arr[0][1]);

	//printf("%p\n", arr[1]);

	system("pause");
	return 0;
}

int main()
{
	//int arr[2][3] = { {1,2,3},{4,5,6} };
	//int arr[2][3] = { 1,2,3,4,5,6 };
	int arr[][3] = { 1,2,3,4,5,6,7 };

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}