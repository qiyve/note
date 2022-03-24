#include<iostream>
using namespace std;
#include<set>
#include<string>

//set容器 排序 存放自定义数据类型

class Person
{
public:

	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

class comparePerson
{
public:

	//作为比较函数后面加const 语法规定 语法规定 语法规定
	bool operator()(const  Person& p1, const  Person& p2)const
	{
		//按年龄大小 降序
		return p1.m_Age > p2.m_Age;
	}
};

void test01()
{
	//自定义数据类型，都会指定排序规则
	set<Person, class comparePerson>s;

	//创建Perosn对象
	Person p1("张三", 40);
	Person p2("阿三", 25);
	Person p3("老王", 30);
	Person p4("老刘", 20);

	s.insert(p1);
	s.insert(p2);
	s.insert(p3);
	s.insert(p4);
	
	//遍历容器
	for (set<Person, class comparePerson>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << "姓名：" << it->m_Name << " 年龄：" << it->m_Age << endl;
	}

}
int main()
{
	test01();
	

	system("pause");
	return 0;
}