#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	

int main()
{
	//所有非0的值都是真值
	//! 非 非真为假 非假为真
	//int a = 10;
	//printf("%d\n", !a);

	//int a = 10;
	//int b = 20;
	////单目运算符高于双目运算符
	////&& 与 同真为真 其余为假
	//printf("%d\n", !a && b);


	int a = 10;
	int b = 0;
    // || 或  
	printf("%d\n", a || b);

	return;
}