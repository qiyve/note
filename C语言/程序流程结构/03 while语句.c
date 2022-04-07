#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main01()
{
	//while (表达式)

	int i = 0;
	//死循环
	while (i<10)
	{
		printf("%d\n", i);
		i++;
	}

	return 0;
}

int main02()
{
	//打印0到100的偶数
	int i = 0;
	while (i<100)
	{
		if (i % 2 == 0)
		{
			printf("%d\n", i);
		}
		i++;
	}

	return 0;
}
int main()
{
	//敲桌子游戏
	//100以内凡是有7 或能被7的倍数打印敲桌子
	int i = 0;

	while (i<100)
	{
		//     7的倍数     个位有7       十位有7
		if (i % 7 == 0 || i % 10 == 7 || i / 10 == 7)
		{
		
			printf("敲桌子\n");
		
		}
		else
		{
			printf("%d\n", i);
		}

		i++;

	}
}