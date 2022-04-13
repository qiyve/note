#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//未初始化全局变量
int a1;
//初始化全局变量
int b1 = 10;
//未初始化静态全局变量
static int c1;
//初始化静态全局变量
static int d1 = 20;

int main()
{
	int e1 = 10;
	//未初始化的静态局部变量
	static int f1;
	//初始化的静态局部变量
	static int h1 = 30;

	//字符串常量
	char* p = "hello world";
	//数组
	int arr[] = { 1,2,3,4, };
	//指针
	int* pp = arr;

	printf("未初始化全局变量：%p\n", &a1);
	printf("初始化全局变量：%p\n", &b1);
	printf("未初始化静态全局变量：%p\n", &c1);
	printf("初始化静态全局变量：%p\n", &d1);
	printf("初始化局部变量：%p\n", &e1);
	printf("未初始化的静态局部变量：%p\n", &f1);
	printf("初始化的静态局部变量：%p\n", &h1);
	printf("字符串常量：%p\n", p);
	printf("数组：%p\n", arr);
	printf("指针变量：%p\n", pp);
	printf("指针地址：%p\n", &pp);


	return 0;
}