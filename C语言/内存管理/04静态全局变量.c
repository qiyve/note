#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//静态全局变量
static int a = 10;

void func1()
{
	a = 20;
	printf("%d\n", a);
}

int main()
{
	printf("%d\n", a);
	func1();
	
	return 0;
}