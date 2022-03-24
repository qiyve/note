#include<iostream>
using namespace std;
#include<string>

//函数对象 (仿函数)

/*
 1.函数对象在使用，可以像普通函数那样调用，可以有参数，可以有返回值
 2.函数对象超出普通函数的概念，函数对象可以有自己的状态
 3.函数对象可以作为参数传递
*/


class MyAdd
{
public:
	int operator()(int v1,int v2)
	{
		return v1 + v2;
	}
};

//1.函数对象在使用，可以像普通函数那样调用，可以有参数，可以有返回值
void test01()
{
	MyAdd myadd;
	cout << myadd(10, 20) << endl;
}

//2.函数对象超出普通函数的概念，函数对象可以有自己的状态
class MyPrint
{
public:

	MyPrint()
	{
		this->count = 0;//初始为0 
	}

	void operator()(string test)
	{
		cout << test << endl;
		count++; //记录调用次数
	}

	int count; //内部自己状态
};

void test02()
{
	MyPrint myprint;
	myprint("hello world");
	myprint("hello world");

	cout << "myprint 调用次数:" << myprint.count << endl;
}

void doPrint(MyPrint& mp, string test)
{
	mp(test);
}

//3.函数对象可以作为参数传递
void test03()
{
	MyPrint myprint;
	doPrint(myprint, "hello C++");

}

int main()
{
	//test01();

	//test02();

	test03();

	system("pause");
	return 0;
}