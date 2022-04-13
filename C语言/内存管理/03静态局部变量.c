#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>


void func1()
{
	//静态局部变量只会初始化一次 可以多次赋值
	static int b = 10;
	b++;
	printf("%d\n", b);

}

int main()
{
	//静态局部变量
	//static int b = 10;
	//printf("%d\n", b);

	for (int i = 0; i < 10; i++)
	{
		func1();
	}
	
	return 0;
}