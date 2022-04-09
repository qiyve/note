#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>



int main01()
{
	/*time_t timer = time(NULL);
	srand((size_t)timer);*/
	//添加随机数种子
	srand((size_t)time(NULL));

	for (int i = 0; i < 10; i++)
	{
		//printf("%d\n", rand() % 100); //0~99  
		printf("%d\n", rand() % 51 + 50); //50~100  
	}

	system("pause");
	return 0;
}

int main()
{
	//双色球 6个红球 1-32  1个蓝球 1-16 
	srand((unsigned int)time(NULL));//随机数种子

	int arr[6] = { 0 };
	int value; //接收随机数
	int	flag = 0;//球数下标
	int j = 0;

	for (int i = 0; i < 6; i++)
	{
		//获取随机数
		value = rand() % 32 + 1; //1~32 
		//去重

		for ( j = 0; j < flag; j++)
		{
			//判断书否有重复 有就多循环一次  
			if (arr[j] == value)
			{
				i--; //(重新循环外层一次，并生成新的随机数）
				break;
			}
		}

		if (j == flag) // 判断 并赋值
		{
			arr[flag] = value;
			flag++;
		}

	}

	for (int i = 0; i < 6; i++)
	{
		printf("%d ", arr[i]);
	}
	//蓝球
	printf("+ %d\n", rand() % 16 + 1);

	system("pause");
	return 0;
}