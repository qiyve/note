//#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	
#pragma warning (disable:4996)

int main(void)
{
	//int a;

	////通过键盘输入赋值
	////&运算符 表示取地址运算符
	//scanf("%d", &a);

	// 青菜 5元/斤 

	const int price = 3; 

	int weight;
	printf("请输入斤数:\n");
	scanf("%d", &weight);

	int sum = price * weight;
	printf("%d\n", sum);
	
	return 0;
}

