#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//break
int main01()
{
	for (int i = 0; i<10 ; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (j == 6)//j=6 退出内侧循环
			{
				break;
			}
			printf("%d %d\n", i, j);
		}
		printf("\n");
	}


	system("pause");
	return 0;
}

//continue 用法
int main02()
{    
	//打印偶数，
	for (int i = 0; i < 20; i++)
	{
		if (i % 2 == 1)
		{
			//终止本次循环，并执行下次循环 
			continue;
		}
		printf("%d\n", i);
	}

	system("pause");
	return 0;
}

//goto
int main03()
{
	printf("hello world 1\n");
	printf("hello world 2\n");

	goto FLAG1;
	printf("hello world 3\n");
	printf("hello world 4\n");


	system("pause");
	return 0;

FLAG1: //此处是 冒号 ：
	printf("hello world 5\n");

	return 1;
}

int main04()
{
	int i = 0, j = 0;


	for ( i = 0; i < 10; i++)
	{
		if (i == 5)
		{
			goto FLAG2;
		}
		printf("i=%d\n", i);
	}

	//j需要赋初始值 以为是直接跳转过来的
	for (j = 0; j < 10; j++)
	{
		FLAG2:
		printf("j=%d\n", j);
		
	}
	system("pause");
	return 0;
}

//伪代码
int main()
{
FLAG:
	
	printf("hello world\n");
	goto FLAG;

	return 0;
}