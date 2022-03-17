#include<iostream>
using namespace std;
#include<string>

//类模板成员函数类外实现

template<class T1,class T2>
class Person
{
public:

	Person(T1 name, T2 age);
	//{
	//	m_Name = name;
	//	m_Age = age;
	//}

	void showPerosn();
	//{
	//	cout << "姓名：" << this->m_Name<< endl;
	//	cout << " 年龄：" << this->m_Age << endl;
	//}

	T1 m_Name;
	T2 m_Age;
};

//构造函数类外实现
template<class T1,class T2>
Person<T1,T2>::Person(T1 name, T2 age)
{
	
	m_Name = name;
	m_Age = age;
		
}

//成员函数类外实现
template<class T1,class T2>
void Person<T1,T2>:: showPerosn()
{
	cout << "姓名：" << this->m_Name 
     << " 年龄：" << this->m_Age << endl;
}


void test01()
{
	Person<string, int>p("阿三", 17);
	p.showPerosn();
}


int main()
{
	test01();

	system("pause");
	return 0;
}