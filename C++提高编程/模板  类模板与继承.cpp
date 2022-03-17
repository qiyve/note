#include<iostream>
using namespace std;
#include<string>

//类模板与继承

//1. 当子类继承的父类是一类模板时，子类在声明的时候，需要指定出父类中T的类型
//2. 如果不指定，编译器无法给予子类分配内存
//3. 如果想灵活指定出父类中 T 的类型，子类也需要变为类模板


template<class T>
class Base
{
public:

	T m;
};

//class Son:public Base //错误，必须要知道父类中的 T 类型,才能继承给子类
class Son1 :public Base<int>
{

};

void test01()
{
	Son1 s1;
}

//如果想灵活指定父类中T类型，子类也需要变成类模板
template<class T1,class T2>
class Son2 :public Base<T2>
{
public:

	Son2()
	{
		cout << "T1 类型：" << typeid(T1).name() << endl;
		cout << "T2 类型：" << typeid(T2).name() << endl;
	}

	T1 obj;
};

void test02()
{
	Son2<int,string>  s2;
}
int main()
{
	test02();

	system("pause");
	return 0;
}