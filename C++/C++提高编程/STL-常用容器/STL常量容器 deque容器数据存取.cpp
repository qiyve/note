#include<iostream>
using namespace std;
#include<deque>

//deque容器数据存取

//at ( int idx );    // 返回索引 idx所指的数据
//operator [ ];      // 返回索引 idx所指的数据
//front（）；        // 返回容器中第一个数据元素
//back（）；         // 返回容器中最后一个数据元素  

void test01()
{
	deque<int>d1;
	d1.push_back(10);
	d1.push_back(20);
	d1.push_back(30);
	d1.push_front(100);
	d1.push_front(200);
	d1.push_front(300);

	//通过[] 方式访问元素
	//300 200 100 10 20 30
	for (int i=0;i<d1.size();i++)
	{
		cout << d1[i]<< " ";
	}
	cout << endl;

	//通过at方式
	//300 200 100 10 20 30
	for (int i = 0; i < d1.size(); i++)
	{
		cout << d1.at(i) << " ";
	}
	cout << endl;

	//访问第一个元素 front()
	cout << "第一个元素：" << d1.front() << endl;

	//访问最后一个元素 back（）；  
	cout << "最后一个元素：" << d1.back() << endl;
}


int main()
{

	test01();
	

	system("pause");
	return 0;
}