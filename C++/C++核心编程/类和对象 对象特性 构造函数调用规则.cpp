#include<iostream>
using namespace std;


// 构造函数调用规则
//1、默认情况下，C++编译器至少给一个类 添加3个函数
// 默认构造（空实现）
// 析构函数（空实现）
// 拷贝构造（值拷贝）

//2、如果我们写了有参构造函数编译器就不再提供默认无参构造，依然提供默认拷贝构造
//   如果用户定义拷贝构造函数，c++不会再提供其他构造层次

class Person
{
public:
	//Person() //默认构造
	//{
	//	cout << "Person默认函数调用" << endl;
	//}

	//Person(int a)//有参构造
	//{
	//	cout << "Person有参构造函数的调用" << endl;
	//	m_Age = a;
	//}

	Person(const Person& p)//拷贝构造
	{
		cout << "Person拷贝构造函数的调用" << endl;
		m_Age = p.m_Age;
	}

	~Person()
	{
		cout << "Person的析构函数的调用" << endl;
	}
	int m_Age;
};


//void test01()
//{
//	Person p;
//	p.m_Age = 18;
//
//	Person p2(p);
//
//	cout << "p2的年龄为："<<p2.m_Age << endl;
//}


void test02()
{
	Person p;
	
}
int main()
{
	//test01();
	
	test02();

	system("pause");
	return 0;
}