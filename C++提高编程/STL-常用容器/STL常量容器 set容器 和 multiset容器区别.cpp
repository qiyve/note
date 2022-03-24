#include<iostream>
using namespace std;
#include<set>

//set容器 和 multiset容器区别


//set 不可以插入重复数据，而multiset可以
//set插入数据的同时会返回插入结果，表示插入是否成功
//multiset不会检测数据，因此可以插入重复数据



void test01()
{
	
	set<int>s;
	
	pair<set<int>::iterator, bool> ret = s.insert(10);

	if (ret.second) //获取bool  为真插入成功
	{
		cout << "第一次插入成功" << endl;
	}
	else
	{
		cout << "第一次插入失败" << endl;
	}

	ret = s.insert(10);

	if (ret.second) 
	{
		cout << "第二次插入成功" << endl;
	}
	else
	{
		cout << "第二次插入失败" << endl;
	}

	//multiset容器
	multiset<int>ms;

	ms.insert(10);
	ms.insert(10);
	ms.insert(10);
	ms.insert(10);

	for (multiset<int>::iterator it = ms.begin(); it != ms.end(); it++)
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