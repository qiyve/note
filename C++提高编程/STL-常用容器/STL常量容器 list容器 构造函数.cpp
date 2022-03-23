#include<iostream>
using namespace std;
#include<list>

//list容器 构造函数

//list<T>;            //list采用采用模板类实现，对象的默认构造形式
//list(beg, end); //构造函数将（beg, end ）区间中的元素拷贝给本身
//list(n, elem);     //构造函数将n个elem拷贝给本身
//list(const list& lst); //拷贝构造函数

void printList(const list<int>&L)
{    //限定只读
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	list<int>L1; //默认构造

	//添加数据
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	printList(L1);

	//区间方式
	list<int>L2(L1.begin(), L1.end());
	printList(L1);

	//n个elem
	list<int>L3(5, 10);
	printList(L3);

	//拷贝构造
	list<int>L4(L3);
	printList(L4);
}



int main()
{
	test01();
	

	system("pause");
	return 0;
}