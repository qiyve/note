#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

int main01()
{
	//外层执行一次  内层执行一周
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("i = %d, j = %d\n", i, j);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}

int main02()
{
	//模拟时钟
	//时针
	for (int i = 0; i < 24; i++)
	{
		//分针
		for (int j = 0; j < 60; j++)
		{
			//秒针
			for (int k = 0; k < 60; k++)
			{
				system("cls");
				printf("%02d:%02d:%02d:\n", i, j, k);
				Sleep(960); //执行到这 休眠一下
			}
		}
		
	}

	return 0;
}
int main()
{
	//九九乘法口诀
	/*
	 1 * 1 = 1
	 2 * 1 = 1  2 * 1 = 2
	 3 * 1 = 1  3 * 2 = 6  3 * 3 = 9
	 */
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			printf("%d*%d=%d\t", i, j,i*j);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}