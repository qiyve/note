#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	

int main()
{
	//比较运算符返回值0或1  1表示真 0表示假
	int a = 10;
	int b = 20;
	int c = 10;

	//printf("%d\n", a == b); // 0
	//printf("%d\n", a != b); // 1
	//printf("%d\n", a <= b); // 1
	//printf("%d\n", a >= b); // 0

	printf("%d\n", c = ++a <= b * 2);
	printf("%d\n", a);
	printf("%d\n", b);
	printf("%d\n", c);
	return;
}