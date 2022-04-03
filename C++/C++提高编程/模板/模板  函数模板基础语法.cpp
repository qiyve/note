#include<iostream>
using namespace std;

//语法 ：template<typename  T>
//函数模板


//交换两个整形函数
void swapInt(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
//交换两个浮点型函数
void swapDouble(double& A, double& B)
{
	double temp = A;
	A = B;
	B = temp;
}

//函数模板
/*声明一个模板，告诉编译器后面
代码中紧跟着的T不要报错，T是一个通用数据类型*/
template<typename T> 
void mySwap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

void test01()
{
	int a = 10;
	int b = 20;
	//swapInt(a,b);
	//利用函数模板交换
	//两种方式使用函数模板
	
	//1、自动类型推导
	//mySwap(a, b);

	//2、显示指定类型
	mySwap<int>(a, b);
	cout << "a= " << a << endl;
	cout << "b= " << b << endl;


	/*double A = 2.1;
	double B = 3.2;
	swapDouble(A, B);
	cout << "A= " << A << endl;
	cout << "B= " << B << endl;*/
}

int main()
{
	test01();

	system("pause");
	return 0;
}