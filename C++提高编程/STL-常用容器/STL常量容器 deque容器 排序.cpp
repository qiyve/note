#include<iostream>
using namespace std;
#include<deque>
#include<algorithm>//标准算法头文件

//deque容器排序
//sort(iterator beg, iterator end);    // 对beg 和end 区间内元素进行排序

void printDeque(const deque<int>&d)//只读
{
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	deque<int>d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(3);
	d.push_front(4);
	d.push_front(5);
	d.push_front(6);

	//6 5 4 1 2 3 
	printDeque(d);

	//排序
	sort(d.begin(), d.end());
	cout << "排序后" << endl;
	printDeque(d);
	
}


int main()
{

	test01();
	

	system("pause");
	return 0;
}