#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int main01()
{
	int j = 0;
	for (int i = 0; i < 10, j < 10; i++, j += 5)
	{
		
		printf("%d\n", i);
	
	}
	return 0;
}
int main02()
{
	int i = 0;

	//死循环 while(1) for(;;)
	for (;;)
	{
		//if (i >= 10)
		//{
		//	//跳出循环
		//	break;
		//}
		printf("%d\n", i);
		i++;
	}

	return 0;
}
int main()
{
	//猜数字
	//通过程序随机一个1-100之间的数

	//产生随机数
	//1、导入随机数 time.h  stdlib.h
	//2、添加随机数种子
	//3、获取随机数
	srand((unsigned int)time(NULL));//每次随机数不一样

	//int value = rand() % 10; //0~9
	//for (int i = 0; i < 10; i++)
	//{
	//	int value = rand() % 10; //0~9
	//	printf("%d\n", value);
	//}
	int value = rand() % 100; //0~99
	int num;
	for(;;)
	{
		printf("请输入数字：\n");
		scanf("%d", &num);

		if (value > num)
		{
			printf("输入值过小\n");
		}
		else if ( value < num)
		{
			printf("输入值过大\n");
		}
		else
		{
			printf("恭喜你猜对了\n");
			break;
		}
		
	}

	system("pause");
	return 0;
}