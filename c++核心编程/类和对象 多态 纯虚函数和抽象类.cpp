#include<iostream>
using namespace std;
#include<string>

//纯虚函数和抽象类
class Base
{
public:

	//纯虚函数
	// 只要有一个纯虚函数，这个类称为纯虚函数
	// 抽象类的特点
	// 1、无法实例化对象
	//2、抽象类的子类 必须要重写父类中的纯虚函数，否则也属于抽象类
	virtual void func() = 0;
};

class Son :public Base
{
public:
	void func()
	{
		cout << "func 函数调用" << endl;
	}
};

void test01()
{
	//Base b;   //抽象类无法实例化对象
	//new Base;// 抽象类无法实例化对象
	//Son s;   // 子类必须重写父类中的纯虚函数

	Base* base = new Son;
	base->func();
}
int main()
{

	test01();




	system("pause");
	return 0;
}