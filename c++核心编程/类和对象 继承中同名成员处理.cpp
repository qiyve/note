#include<iostream>
using namespace std;


//继承中同名成员处理

class Baese
{
public:

	Baese()
	{
		m_A = 10;
	}

	void func()
	{
		cout << "Baese 函数调用" << endl;
	}
	void func(int)
	{
		cout << "Baese int 函数调用" << endl;
	}

	int m_A;
};

class Son:public Baese
{
public:
	Son()
	{
		m_A = 100;
	}

	void func()
	{
		cout << "Son 函数调用" << endl;
	}
	int m_A;
};

//同名成员属性
void test01()
{
	Son s;

	cout << "Son 下 m_A= " << s.m_A << endl;
	//如果通过子类对象 访问到父类中同名成员，需要加作用域
	cout << "Baese 下 m_A= " << s.Baese::m_A << endl;
}

//同名成员函数
void test02()
{
	Son s;
	s.func();//直接调用，调用是子类中的同名成员

	//如何调用到父类中同名成员函数？
	s.Baese::func();

	//如果子类中出现和父类相同名成员函数，子类的同名成员会隐藏掉父类中所有同名成员函数
	//如果想访问父类中被隐藏的同名成员函数，需要加作用域
	s.Baese::func(100);
}

int main()
{
	
	//test01();

	test02();

	system("pause");
	return 0;
}