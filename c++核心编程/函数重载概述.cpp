#include<iostream>
using namespace std;

//函数重载
// 函数名可以相同，提高复用性
//可以让函数名相同，提高函数的复用性

// (1)同一个作用域下                         
//( 2)  函数名相同
//（3） 函数参数类型不同或者个数不同 或者 顺序不同

//个数不同
void func()
{
	cout << "func的调用" << endl;
}
void func(int a)
{
	cout << "func(int a)" << endl;
}

//类型不同
void func(int a)
{
	cout << "func(int a)" << endl;
}
void func(double a)
{
	cout << "func(double a)" << endl;
}



//顺序不同
void func(double a,int b)
{
	cout << "func(double a,int b)" << endl;
}
void func( int b,double a )
{
	cout << "func(int b,double a)" << endl;
}
//注意事项
//函数的返回值不可以作为函数重载的条件
//int func(int b, double a)
//{
//	cout << "func(int b,double a)" << endl;
//}

int main()
{
	//个数不同
	func();
	func(10);

	//类型不同
	func(10);
	func(3.14);

	//顺序不同
	func(3.14, 10);
	func(10, 3.14);


	

	system("pause");
	return 0;
}

