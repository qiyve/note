#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<string>

//常用查找算法  find_if

//find(iterator beg, iterator end, _pred);
//按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器
//beg 开始迭代器
//end 结束迭代器
//_pred 函数或者谓词 （返回bool类型的仿函数）
//利用find可以在容器中找指定的元素，返回值是迭代器

//1、查找内置数据类型
class GreaterFive
{
public:

	bool operator()(int val)
	{
		return val > 5;
	}
};
void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	//查找大于5 的元素
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());
	if (it == v.end())
	{
		cout << "未找到" << endl;
	}
	else
	{
		cout << "找到大于5的元素：" << *it << endl;
	}
}

//2、查找自定义数据类型
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

//谓词
class Greater20
{
public:
	bool operator()(const Person& p)
	{
		return  p.m_Age > 50;
	}
};


void test02()
{
	vector<Person>v;

	//创建数据
	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);

	//找年龄大于20的人
	vector<Person>::iterator it = find_if(v.begin(), v.end(), Greater20());

	if (it == v.end())
	{
		cout << "未找到" << endl;
	}
	else
	{
		cout << "找到了 姓名：" << it->m_Name << " 年龄：" << (*it).m_Age << endl;
	}
}
int main()
{
	//test01();
	test02();

	system("pause");
	return 0;
}