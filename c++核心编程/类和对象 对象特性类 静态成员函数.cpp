#include<iostream>
using namespace std;


//静态成员函数
//所有对象共享同一个函数
//静态成员函数只访问静态成员变量



class  Person
{
public:

	//静态成员函数  在前面加上 static
	static void func()
	{
		cout << "static void func调用" << endl;
	}

};

void test01()
{
	//1.通过对象访问
	Person p;
	p.func();

    //2.通过类名访问
	Person::func;
}
int main()
{
	test01();

	system("pause");
	return 0;
}