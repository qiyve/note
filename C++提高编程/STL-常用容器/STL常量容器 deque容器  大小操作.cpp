#include<iostream>
using namespace std;
#include<deque>

// deque容器大小操作

//deque.empty();       //判断容器是否为空
//deque.size();        //返回容器中元素的个数
//deque.resize(num);   //重新指定容器的长度为num，若容器变长，则以默认值填充
					   //如果容器变短，则末尾超出容器长度的元素被删除。
//deque.resize(num, elem);//重新指定容器长度为num，若容器变长，则以elem值填充新位置
						  //如果容器长度变短，则末尾超出容器长度的元素被删除

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
	deque<int>d;
	for (int i = 0; i < 10; i++)
	{
		d.push_back(i);
	}
	printDeque(d);

	if (d.empty()) //为真  容器为空
	{
		cout << "容器为空" << endl;
	}
	else
	{
		cout << "容器大小为：" << d.size() << endl;
	}

	//重新指定容器大小
	//d.resize(15);  如果定义容器变长，则以默认值填充
	d.resize(5);
	printDeque(d);

}



int main()
{

	test01();

	

	system("pause");
	return 0;
}