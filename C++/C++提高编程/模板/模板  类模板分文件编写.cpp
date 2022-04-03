#include<iostream>
using namespace std;
#include<string>

//源码

//类模板分文件编写问题以及解决
//总结：主流的解决方法是第二种，将类模板成员函数写到一起，并将后缀名改为 .cpp 

//第一种解决方式：直接包含 源文件
// #include"Person.cpp"

//第二种解决方式：将 .h 和 .cpp内容写到一起，将后缀名为 .hpp   .hpp是约定的名称
#include"Person.hpp"

//template<class T1,class T2>
//class Person
//{
//public:
//
//	Person(T1 name, T2 age);
//
//	void showPerson();
//
//	T1 m_Name;
//	T2 m_Age;
//};

////类外实现构造函数
//template<class T1,class T2>
//Person<T1, T2>::Person(T1 name, T2 age)
//{
//	m_Name = name;
//	m_Age = age;
//}
//
////类外实现成员函数
//template<class T1, class T2>
//void Person<T1, T2>::showPerson()
//{
//	cout << "姓名：" << this->m_Name << " 年龄：" << m_Age << endl;
//}

void test01()
{
	Person<string, int>p("Tom", 18);
	p.showPerson();
}

int main()
{
	test01();

	system("pause");
	return 0;
}