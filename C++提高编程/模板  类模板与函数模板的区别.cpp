#include<iostream>
using namespace std;
#include<string>

//语法：  template<typename T>  //   typenname 可以用class代替


//类模板
template <class NameType,class AgeType=int>
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
		cout << "name：" << m_Name << " age：" << m_Age << endl;
	}


	NameType m_Name;
	AgeType m_Age;
};
//1.类模板没有自动类型推导的使用方式
void test01()
{
	// Person p1("阿三", 15); 错误，无法用自动类型推导

	//利用指定类型显示
	Person<string, int>p1("阿三", 15);
	p1.showPerson();
}

//2.类模板在模板参数列表中可以有默认参数
void test02()
{
	Person<string>p2("张三", 15);
	p2.showPerson();
}

int main()
{
	test01();

	test02();
	
	system("pause");
	return 0;
}