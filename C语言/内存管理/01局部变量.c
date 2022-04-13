#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

void func1(int a)
{
	int b = 20;
}

int main()
{
	//定义变量  局部变量 在函数内部定义的变量
	//作用域：在函数内部
	//生命周期：从创建到函数结束
	auto int a = 10;

	int i;
	for ( i = 0; i < 10; i++)
	{

	}
	printf("%d\n", i);
	printf("%d\n", a);


	return 0;
}