#include<iostream>
using namespace std;

//this指针的用途：

class Person
{
public:
	
	Person(int age)
	{
		//age = age; 错误   当形参和成员变量同名时，可用this指针来区分

		//this指针指向 被调用的成员函数 所属的对象
		this->age = age;
	}

	Person & PersonAddAge(Person& p)
	{
		this->age += p.age;

		//this指向p2的指针，而*this指向的就是p2这个对象本体
		return *this;

	}

	int age;//属性
};

//1、解决名称冲突
void test01()
{
	Person p(18);
	cout << "p的年龄为：" << p.age << endl;
}

//2、返回对象本身用 *this
void test02()
{
	Person p1(10);
	Person p2(10);

	p2.PersonAddAge(p1).PersonAddAge(p1).PersonAddAge(p1);

	cout << "p的年龄为：" << p2.age << endl;
}

int main()
{

	//test01();

	test02();

	system("pause");
	return 0;
}