#include<iostream>
using namespace std;
#include<string>
#include<list>


//list容器 排序案例 对于自定义数据类型 做排序

//案例描述： 将Person自定义数据类型进行排序，Person中属性有姓名、年龄、身高
//排序规则： 按照年龄进行升序，如果年龄相同按照身高进行降序


class Person
{
public:
	Person(string name, int age, int hg)
	{
		this->m_Name = name;
		this->m_Age = age;
		this->m_Height = hg;
	}


	string m_Name; //姓名
	int  m_Age;  // 年龄
	int m_Height;//身高
};

//指定排序规则
bool comparPerson(Person& p1, Person p2)
{
	//按年龄 升序  如果年龄相同 按身高降序
	if (p1.m_Age == p2.m_Age)
	{
		//按身高 降序
		return p1.m_Height > p2.m_Height;
	}
	else
	{
		return p1.m_Age < p2.m_Age;
	}
}

void test01()
{
	list<Person>L;

	//准备数据
	Person p1("刘备", 25, 170);
	Person p2("关羽", 30, 175);
	Person p3("曹操", 40, 160);
	Person p4("张飞", 30, 180);
	Person p5("赵云", 30, 190);
	Person p6("孙权", 35, 195);

	//插入数据
	L.push_back(p1);
	L.push_back(p2);
	L.push_back(p3);
	L.push_back(p4);
	L.push_back(p5);
	L.push_back(p6);

	for (list<Person>::iterator it = L.begin(); it != L.end(); it++)
	{
		cout << "姓名：" << (*it).m_Name 
			<< " 年龄：" << (*it).m_Age  // 也利用指针获取数据
			<< " 身高：" << it->m_Height << endl;
	}

	//排序
	cout << "------------------------------" << endl;
	cout << "排序后：" << endl;

	L.sort(comparPerson);

	for (list<Person>::iterator it = L.begin(); it != L.end(); it++)
	{
		cout << "姓名：" << (*it).m_Name
			<< " 年龄：" << (*it).m_Age  
			<< " 身高：" << it->m_Height << endl;
	}
}

int main()
{
	test01();
	
	

	system("pause");
	return 0;
}