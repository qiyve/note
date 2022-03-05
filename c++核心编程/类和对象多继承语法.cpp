#include<iostream>
using namespace std;


//多继承语法

//创建父类
class Baese1
{
public:

	Baese1()
	{
		m_A = 100;
	}
	int m_A;
};

class Baese2
{
public:

	Baese2()
	{
		m_A = 200;
	}
	int m_A;
};

//子类 需要继承Baese1和Baese2
//语法： class 子类 ：继承方式  父类，继承方式  父类2 ...
class Son:public Baese1,public Baese2
{
public:
	Son()
	{
		m_C = 300;
		m_D = 400;
	}
	int m_C;
	int m_D;
};

void test01()
{
	Son s;
	cout << "Son所占内存：" << sizeof(s) << endl;
	//当父类中出现同名成员，需要加作用域区分
	cout << "Baese1::m_A= " << s.Baese1::m_A << endl;
	cout << "Baese2::m_A= " << s.Baese2::m_A << endl;
}

int main()
{
	test01();
	

	system("pause");
	return 0;
}