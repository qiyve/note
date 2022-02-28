#include<iostream>
using namespace std;


//对象的初始化和清理
// 1、构造函数 进行初始化操作
class Person
{
public:
	//1、构造函数 
   // 没有函数返回值 不写void
   // 函数名 与类名相同
   // 构造函数可以有参数，可以发生重载
    //创建对象时，构造函数会自动调用，而且只会调用一次

	Person()
	{
		cout << "构造函数Person的调用" << endl;
	}

	 //2、析构函数 进行清理空间
	
	 //析构函数，没有返回值也不写void
	 //函数名称与类名相同，在名称前加上符号 ~
	 //析构函数不可以有参数值，因此不可以发生重载
     //程序在对象销毁前会自动调用析构，无需手动调用，而且只会调用一次
	~Person()
	{
		cout << "析构函数Person的调用" << endl;
	}
};

//构造和析构都是必须有的实现，如果我们自己不提供，编译器会提供一个空实现的构造和析构
void test01()
{
	Person p;//在栈的数据，test01执行完毕后，就会释放这个对象
}

int main()
{

	test01();

	//Person p;



	system("pause");
	return 0;
}