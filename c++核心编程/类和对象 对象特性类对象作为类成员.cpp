#include<iostream>
using namespace std;
#include<string>


//类对象作为类成员


//手机类
class Phone
{
public:

	Phone(string pName)
	{
		m_PName = pName;

		cout << "Phone的构造函数调用" << endl;
	}
	~Phone()
	{
		cout << "Phone的析构函数调用" << endl;
	}

	//手机品牌
	string m_PName;
	
};

//人类
class Person
{
public:

	//phone m_phone = pName   隐式转换法
	Person(string name, string pName):m_Name(name),m_phone(pName)
	{
		cout << "Person的构造函数调用" << endl;
	}

	~Person()
	{
		cout << "Person的析构函数调用" << endl;
	}

	//姓名
	string m_Name;

	//手机
	Phone m_phone;

};

//当其他类对象作为本类成员，构造时候先构造类对象，在构造自身

void test01()
{
	Person p("阿三","苹果MAX");

	cout << p.m_Name << "拿着：" << p.m_phone.m_PName << endl;
}
int main()
{
	test01();

	system("pause");
	return 0;
}