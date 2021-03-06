#include<iostream>
using namespace std;
#include<set>

//set容器 构造和赋值

//构造：
//set <T>st;           //默认构造函数
//set(const set& st); //拷贝构造函数

//赋值：
//set& operator=(const set& st);   //重载等号运算符
void printSet(set<int>&s)
{
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void test01()
{
	set<int>s1;
	
	//插入数据  只有insert方式
	s1.insert(10);
	s1.insert(40);
	s1.insert(20);
	s1.insert(30);
	s1.insert(30);

	//遍历容器
	//set容器特点：1、所有元素在插入的时候自动被排序
	//             2、set不允许容器中有重复的元素
	printSet(s1);

	//拷贝构造
	set<int>s2(s1);
	printSet(s2);

	//赋值  operator=
	set<int>s3;
	s3 = s2;
	printSet(s3);
}

int main()
{
	test01();
	
	

	system("pause");
	return 0;
}