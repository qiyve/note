#include<iostream>
using namespace std;
#include<string>

//函数调用运算符重载

//打印函数输出类
class MyPrint
{
public:

	//重载 函数调用运算符
	void operator()(string test)
	{
		cout << test << endl;
    }
	
}; 
//普通打印函数
void MyPrint02(string test)
{
	cout << test << endl;
}


void test01()
{
	MyPrint myprint;

	myprint("hello world");//由于使用起来非常类似于函数调用，因此称为仿函数

	MyPrint02("hello world");

}

//仿函数非常灵活没有固定写法
//加法类

class MyAdd
{
public:

	int operator()(int num1,int num2)
	{
		return num1 + num2;
	}
};

void test02()
{
	MyAdd myadd;

	int ret=myadd(100, 100);

	cout<< "ret=:" << ret << endl;

	//匿名函数对象
	cout << MyAdd()(100, 100) << endl;
}

int main()
{
	test01();

	test02();

	system("pause");
	return 0;
}