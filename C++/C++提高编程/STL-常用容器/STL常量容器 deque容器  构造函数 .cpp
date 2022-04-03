#include<iostream>
using namespace std;
#include<deque>

// deque 构造函数

//deque<T>deq;               //默认构造形式
//deque(beg, end);           //构造函数将（beg ，end) 区间的元素拷贝给本身
//deque(n, elem);            //构造函数将n个elem拷贝给本身
//deque(const deque& deq);   //拷贝构造函数      

void printDeque(const deque<int>& d)
{
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		//*it=100; 容器的数据不可以修改了
		
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	deque<int>d1;
	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
	}
	printDeque(d1);

	//区间
	deque<int>d2(d1.begin(), d1.end());
	printDeque(d2);

	deque<int>d3(5, 10);
	printDeque(d3);

	deque<int>d4(d3);
	printDeque(d4);

}



int main()
{

	test01();

	

	system("pause");
	return 0;
}