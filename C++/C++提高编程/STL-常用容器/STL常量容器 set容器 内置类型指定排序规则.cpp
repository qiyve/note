#include<iostream>
using namespace std;
#include<set>

//set容器 排序

//利用仿函数，可以改变排序规则
class MyCompare
{
public:
	//声明一个成员函数的时候用const关键字是用来说明这个函数是 “只读(read-only)”函数，
	//也就是说明这个函数不会修改任何数据成员(object)。
	bool operator()( int v1, int  v2) const
	{
		return v1 > v2;
	}
};


void test01()
{
	set<int>s1;

	s1.insert(10);
	s1.insert(40);
	s1.insert(50);
	s1.insert(30); 
	s1.insert(20);

	for (set<int>::iterator it = s1.begin(); it != s1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	//指定排序规则 从大到小 
	//作为比较函数后面加const 语法规定 语法规定 语法规定
	set<int, MyCompare>s2;

	s2.insert(10);
	s2.insert(40);
	s2.insert(50);
	s2.insert(30);
	s2.insert(20);
	
	for (set<int, MyCompare>::iterator it = s2.begin(); it != s2.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
int main()
{
	test01();
	

	system("pause");
	return 0;
}