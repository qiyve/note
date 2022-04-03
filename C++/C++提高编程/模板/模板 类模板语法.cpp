#include<iostream>
using namespace std;
#include<string>

//类模板
template <class NameType,class AgeType>
class Person
{
public:

	Person(NameType name,AgeType age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	void showPerson()
	{
		cout << "姓名：" << m_Name << "年龄：" << m_Age << endl;
	}


	NameType m_Name;
	AgeType m_Age;
};

void test01()
{
	Person<string, int>p1("阿三", 17);
	p1.showPerson();
}
int main()
{
	test01();

	
	system("pause");
	return 0;
}