#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<string>


//常用查找算法  count


//count(iterator beg, iterator end, value);
//统计元素出现次数
//beg 开始迭代器
//end 结束迭代器
//value 统计的元素

//1、统计内置数据类型
void test01()
{
	vector<int>v;
	v.push_back(10);
	v.push_back(30);
	v.push_back(20);
	v.push_back(30);
	v.push_back(20);
	v.push_back(20);

	int num = count(v.begin(), v.end(), 20);
	
	cout << "20的元素个数：" << num << endl;
}

//2、统计自定义数据类型
class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	bool operator==(const Person& p)
	{
		if (this->m_Age == p.m_Age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string m_Name;
	int m_Age;
};

void test02()
{
	vector<Person>v;

	Person p1("aa", 10);
	Person p2("bb", 20);
	Person p3("cc", 40);
	Person p4("dd", 30);
	Person p5("ee", 10);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);

	//统计和ss 同岁数的人
	Person p("ss", 10);
	
	int num = count(v.begin(), v.end(),p);

	cout << "和ss同岁数的人员个数：" << num << endl;



}
int main()
{
	//test01();
	
	test02();

	system("pause");
	return 0;
}