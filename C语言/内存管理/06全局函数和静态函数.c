#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

// 函数可以调用自己  成为递归函数
void print()
{
	printf("hello world\n");

}

int main01()
{
	//全局函数的名称是作用域中唯一的
	//作用域：在整个项目中所有中使用
	print();
	
	return 0;
}

//静态函数
static void func2()
{
	printf("hello world\n");

}

int main()
{
	func2();

	return 0;
}