#include<iostream>
using namespace std;

//栈区数据 注意事项： 不要返回局部变量的地址
//栈区数据由编译器管理开辟和释放

int*func(int b)//形参数据也会放在栈区
{
	b = 100;

	int a = 10; //局部变量
	return &a;//返回局部变量的地址
}

int main()
{

	int* p = func();
	cout << *p << endl;//第一次可以打印正确的，是因为编译器做了保留
	cout << *p << endl;//第二次这个数据就不再保留了




	system("pause");
	return 0;
}