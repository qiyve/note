#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main()
{
	//声明
	//extern int a;
	////定义
	//int a = 10;

	//char a = 'a'; 'a'占一个字节  
	//char b = "b"; 占两个两个字节 "b\0"

	//遇到\0停止
	//char* b = "hello\0 world";

	char b[11] = "hello world";

	//占位符 %s 表示输出字符串
	printf("%s\n", b);






	return 0;
}