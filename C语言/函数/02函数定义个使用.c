#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>


//返回值类型 函数名（参数列表）
//{
//  代码体
// return 0；
//}
//函数定义
int add(int a, int b)
{
	//int sum = a + b;
	//return sum;

	return a + b;
}

void print()
{
	printf("hello world");
}

//交换
void swap(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;


}
int main()
{

	int a = 10;
	int b = 20;
	//函数调用
	int c = add(a, b);

	//printf("%d\n", c);
	//print();
	
	printf("交换前：\n");
	printf("a= %d\n", a);
	printf("b= %d\n", b);

	swap(a, b);
	printf("交换后：\n");
	printf("a= %d\n", a);
	printf("b= %d\n", b);

	system("pause");
	return 0;
}