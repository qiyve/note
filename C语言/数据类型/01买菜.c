#include<stdio.h>

int main01()
{
	//黄瓜 3元/斤   购买5斤
	//常量：在程序运行过程中，其值不能被改变的量 称为常量
	
	const int price = 3; //常量 只读变量
	//price = 5;  err（错误）

	//变量 在程序运行过程中，其值可以改变 成为变量
	int weifht = 5;

	int sum = price * weifht;

	printf("%d\n", sum);
	return 0;
}