#include<iostream>
using namespace std;
#include<set>

//set容器  大小和交换


//size（）；     //返回容器中元素的数目
//empty（）； //判断容器是否为空
//swap（）；   //交换两个集合容器


void printSet(set<int>&s)
{
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//大小
void test01()
{
	set<int>s1;
	
	//插入数据  只有insert方式
	s1.insert(10);
	s1.insert(20);
	s1.insert(30);
	s1.insert(40);
	
	//打印容器
	printSet(s1);

	//判断容器是否为空
	if (s1.empty())
	{
		cout << "s1 为空" << endl;
	}
	else
	{
		cout << "s1 不为空" << endl;
		cout << "元素的个数为：" << s1.size() << endl;
	}
}

//交换
void test02()
{
	set<int>s1;
	//插入数据  只有insert方式
	s1.insert(10);
	s1.insert(20);
	s1.insert(30);
	s1.insert(40);

	set<int>s2;
	//插入数据  只有insert方式
	s2.insert(1);
	s2.insert(2);
	s2.insert(3);
	s2.insert(4);

	cout << "交换前" << endl;
	printSet(s1);
	printSet(s2);
	
	//交换
	s2.swap(s1);
	cout << "交换后" << endl;
	printSet(s1);
	printSet(s2);
}
int main()
{
	//test01();
	
	test02();

	system("pause");
	return 0;
}