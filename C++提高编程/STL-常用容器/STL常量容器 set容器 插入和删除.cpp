#include<iostream>
using namespace std;
#include<set>

//set容器  插入和删除


//insert(elem);         //在容器中插入元素
//clear();                   //清除所有元素
//erase();                 //删除pos迭代器所指的元素，返回下一个元素的迭代器
//erase(beg, end);  //删除区间（beg，end）的所有元素，返回下一个元素的迭代器
//erase(elem);         //删除容器中值为elem的元素


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
	
	//插入  只有insert方式
	s1.insert(10);
	s1.insert(40);
	s1.insert(20);
	s1.insert(30);

	printSet(s1);

	//删除
	s1.erase(s1.begin());
	printSet(s1);

	//删除重载版本
	s1.erase(40);
	printSet(s1);

	//清空
	//s1.erase(s1.begin(), s1.end()); //区间删除
	s1.clear();
	printSet(s1);
	
}

int main()
{
	test01();
	
	

	system("pause");
	return 0;
}