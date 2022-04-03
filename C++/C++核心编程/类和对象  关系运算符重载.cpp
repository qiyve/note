#include<iostream>
using namespace std;
#include<string>

//关系运算符重载
class Person
{
public:

	Person(string name,int age)
	{
		m_Name = name;
		m_Age = age;
	}
	//重载 == 号
	bool operator==(Person &p)
	{
		//判断是否相等 相等返回一个真 true  不相等返回假 false
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
		{
			return true;
		}
		return false;
	}

	//重载 ！= 号
	bool operator!=(Person & p)
	{
		//判断是否不相等 不相等返回真 true  相等返回假 false
		if (this->m_Name != p.m_Name && this->m_Age != p.m_Age)
		{
			return true;
		}
		return false;
	}

public:

	string m_Name;

	int m_Age;
};

void test01()
{
	Person p1("Tom", 10);

	Person p2("Tom", 10);

	if (p1 == p2)
	{
		cout << "p1和p2是相等的！" << endl;
	}
	else
	{
		cout << "p1和p2是不相等的！" << endl;
	}

	if (p1 != p2)
	{
		cout << "p1和p2不相等" << endl;
	}
	else
	{
		cout << "p1和p2相等" << endl;
	}
}



int main()
{
	test01();

	

	system("pause");
	return 0;
}