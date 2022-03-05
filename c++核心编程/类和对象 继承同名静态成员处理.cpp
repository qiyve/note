#include<iostream>
using namespace std;


//继承中同名成员处理

class Baese
{
public:

	static int m_A;
	static void func()
	{
		cout << "Baese -func调用" << endl;
	}
	static void func(int a)
	{
		cout << "Baese -func int a调用" << endl;
	}
};
int Baese::m_A = 100;

class Son:public Baese
{
public:
	
	static int m_A;
	static void func()
	{
		cout << "Son -func调用" << endl;
	}
};

int Son::m_A = 200;

//同名静态成员访问
void test01()
{
	//通过对象访问
	cout << "通过对象访问" << endl;
	Son s;
	cout << "Son下m_A= " << s.m_A << endl;
	cout << "Baese下m_A= " << s.Baese::m_A << endl;

	//通过类名访问
	cout << "通过类名访问" << endl;
	cout << "Son下m_A= " << Son::m_A<< endl;
	//第一个::代表通过类名方式访问  第二个::代表访问父类作用域下	·
	cout << "Baese下 m_A= " << Son::Baese::m_A << endl;
}


//同名静态成员函数
void test02()
{
	//1、通过对象访问
	cout << "通过对象访问" << endl;
	Son s;
	s.func();
	s.Baese::func();

	//2/通过类名访问
	cout << "通过类名访问" << endl;
	Son::func();
	Son::Baese::func();

	//子类出现和父类同名静态成员函数，也会隐藏掉父类中所有同名成员函数
	//如果想访问父类中被隐藏的同名成员函数，需要加作用域
	Son::Baese::func(100);

}

int main()
{
	
	test01();

	test02();

	system("pause");
	return 0;
}