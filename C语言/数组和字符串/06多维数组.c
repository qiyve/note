#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

int main01()
{   
	//一维数组：
	//数据类型 数组名[元素个数]
	//二维数组：
	// 数据类型 数组名[行][列]
	
	//三维数组
	//数据类型 数组名[层][行][列]

	int arr[2][3][4] =
	{
	   {
		   {1,2,3,4},
		   {2,3,4,5},
		   {3,4,5,6},
	   },
		{
			{4,5,6,7},
			{5,6,7,8},
			{6,7,8,9},
		}
	};
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				printf("%d ", arr[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
	
	printf("三维数组大小：%d\n", sizeof(arr));// 2*3*4*4 层*行*列*sizeof(数据类型)
	printf("三维数组一层大小：%d\n", sizeof(arr[0]));
	printf("三维数组一行大小：%d\n", sizeof(arr[0][0]));
	printf("三维数组一元素大小：%d\n", sizeof(arr[0][0][0]));


	printf("层数：%d\n", sizeof(arr)/sizeof(arr[0]));
	printf("行数：%d\n", sizeof(arr[0]) / sizeof(arr[0][0]));
	printf("列数：%d\n", sizeof(arr[0][0]) / sizeof(arr[0][0][0]));



	system("pause");
	return 0;
}

int main()
{
	int arr[2][3][4][5] = { 1,2,3 };
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				for (int l = 0; l < 5; l++)
				{
					printf("%d ", arr[i][j][k][l]);
				}
				printf("\n");
			}
			printf("\n");
		}
		
	}


	system("pause");
	return 0;
}