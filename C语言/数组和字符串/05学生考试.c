#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

int main()
{
	//定义一个数组 存储五名学生三门成绩 
	//求出每个学生的总成绩 平均成绩
	//求出每门学科的总成绩 平均成绩
	int arr[5][3];

   //获取学生成绩
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			scanf("%d", &arr[i][j]);
		}
	}

	//打印学生成绩
	for (int i = 0; i < 5; i++)
	{
		int sum = 0;
		for (int j = 0; j < 3; j++)
		{
			sum += arr[i][j];
			//printf("%d", arr[i][j]);
		}
		printf("第%d名学生总成绩：%d\t 平局成绩：%d\n", i + 1, sum, sum / 3);
	}

	//每个总成绩 及平均分
	for (int i = 0; i < 3; i++)
	{
		int sum = 0;
		for (int j = 0; j < 5; j++)
		{
			sum += arr[j][i];
			
		}
		printf("第%门的总成绩：%d\t 平局成绩：%d\n", i + 1, sum, sum / 3);
	}

	system("pause");
	return 0;
}