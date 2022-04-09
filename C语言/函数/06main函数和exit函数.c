#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

//函数声明
//extern int add(int a, int b);
//int add(int a, int b);
int add(int, int);

int main()
{
	
	//函数调用
	add(10, 20);
	int a = add(10, 20);
	printf("%d\n", a);

	system("pause");
	return 0;
}

//函数定义 只能定义一次
int add(int a,int b)
{
	return a + b;
}