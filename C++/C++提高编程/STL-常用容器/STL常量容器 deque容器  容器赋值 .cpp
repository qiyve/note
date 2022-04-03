#include<iostream>
using namespace std;
#include<deque>

// deque容器赋值

//deque& operator= (const deque& ded);   // 重载等号操作符
//assign （ beg ，end);    //将（beg ，end）区间中的数据拷贝赋值给本身
//assign （ n ， elem ）；  //将n个elem拷贝赋值给本身

void printDeque(const deque<int>& d)
{ 
	  //如果想限定容器只读状态    利用 const_iterator 只读迭代器   
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

	//利用operator= 
	deque<int>d2;
	d2 = d1;
	printDeque(d2);

	// assign 区间赋值
	deque<int>d3;
	d3.assign(d1.begin(),d1.end());
	printDeque(d3);

	// assign  将n个elem拷贝赋值给本身
	deque<int>d4;
	d4.assign(5, 10);
	printDeque(d4);
	
}



int main()
{

	test01();

	

	system("pause");
	return 0;
}