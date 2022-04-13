#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//为初始化的全局变量
//int abc;
//未初始化的静态全局变量
//static int abc;

int main()
{
	//int abc;
	static int abc;
	//局部变量未初始化 值为乱码
	printf("%d\n", abc);
	
	
	return 0;
}