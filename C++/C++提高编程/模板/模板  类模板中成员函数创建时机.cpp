#include<iostream>
using namespace std;
#include<string>
//  类模板中成员函数创建时机
//  类模板中成员函数和普通类中成员函数创建时机是有区别的：

//1. 普通类中的成员函数一开始就可以创建
//2. 类模板中的成员函数在调用时才创建

//总结： 类模板中的成员函数并不是一开始就创建的，在调用时才去创建

class Person1
{
public:

	void showPerson1()
	{
		cout << "Person1 show" << endl;
	}
};

class Person2
{
public:

	void showPerson1()
	{
		cout << "Person2 show" << endl;
	}
};

template<class T>
class myCalss
{
public:

	T ojb;

	//类模板中的成员函数
	void func1()
	{
		ojb.showPerson1();
	}
	void func2()
	{
		ojb.showPerson2();
	}
};

void test01()
{
	myCalss<Person1>m;
	m.func1();
	//m.func2();

}

int main()
{
	test01();

	
	
	system("pause");
	return 0;
}