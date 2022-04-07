#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX(a,b) (a)>(b)?(a):(b)

int main()
{
	int a = 20;
	int b = 30;
	printf("最大值为：%d\n", MAX(a, b));

	return 0;
}


int main01()
{
	int a = 10;
	int b = 20;
	int c = 30;
	//表示1 ？表达式2:表达式3
	//c = a > b ? a : b;
	//printf("最大值为：%d\n", c);

	printf("最大值为：%d\n", a > b ? a : b);

	printf("最大值为：%d\n", a > b ? (a > c ? a : c) : (b > c ? b : c));
	//if (a > b)
	//{
	//	printf("a大\n");
	//}
	//else
	//{
	//	printf("b大\n");
	//}



	system("pause");
	return 0;
}