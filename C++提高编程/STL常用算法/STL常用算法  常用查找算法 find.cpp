#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<string>


//常用查找算法  find

//find(iterator beg, iterator end, value);
//按值查找元素，找到返回指定位置的迭代器，找不到返回结束迭代器位置
//beg 开始迭代器
//end 结束迭代器
//value 查找的元素

//查找 内置数据类型
void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	//查找 容器中 是否有 5这个元素存在
	vector<int>::iterator it = find(v.begin(), v.end(), 5);
	if (it == v.end())
	{
		cout << "没有找到" << endl;
	}
	else
	{
		cout << "找到到元素 ：" << *it << endl;
	}
	
}

class Person
{
public:
	Person(string name, int age)
	{
		this->m_Nmae = name;
		this->m_Age = age;
	}

	//重载 == 底层find知道如何对比Person数据类型
	bool operator==(const Person &p)
	{
		if (this->m_Nmae == p.m_Nmae && this->m_Age == p.m_Age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	string m_Nmae;
	int m_Age;

};
//查找 自定义数据类型
void test02()
{
	vector<Person>v;
    
	Person p1("张三", 15);
	Person p2("老三", 35);
	Person p3("老刘", 65);
	Person p4("老张", 25);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);

	Person pp("张三", 15);

	vector<Person>::iterator it = find(v.begin(), v.end(), pp);
	if (it == v.end())
	{
		cout << "未找到" << endl;
	}
	else
	{
		cout << "找到了 --- 姓名：" << it->m_Nmae << " 年龄：" << it->m_Age << endl;
	}


}

int main()
{
	//test01();
	test02();

	system("pause");
	return 0;
}