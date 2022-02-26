#include<iostream>
using namespace std;

//函数默认参数

//语法  返回值类型 函数名 （形参 =默认值）{ }
int func(int a = 10, int b = 20, int c = 30)
{
	return (a + b + c);
}

//如果我们自己传入数据，就用自己的数据，如果没有哪么就用默认值
int func02(int a, int b=20 , int c = 40)
{
	return (a + b + c);
}

//注意事项
//1、如果某个位置已经有了默认参数，那么从这个位置往后，从(当前位置）左到右都必须有默认值

//int func(int a=10,int b,int c) //错误 某个位置有了默认参数，往后从左到右都必须有默认值


//2、如果函数的声明有默认参数，函数实现就不能有默认参数
//声明和实现只能有一个有默认参数
int func03(int a = 10, int b = 10);

int func03(int a, int b)
{
	return (a + b);
}
int main()
{

	cout << func() << endl;

	cout << func02(20,30) << endl;

	cout << func03() << endl;

	system("pause");
	return 0;
}

