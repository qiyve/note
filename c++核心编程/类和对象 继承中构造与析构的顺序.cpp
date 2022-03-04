#include<iostream>
using namespace std;
#include<string>

//继承中构造和析构顺序

//公共继承
class Baese
{
public:
	
	Baese()
	{
		cout << "Baese的构造函数" << endl;
	}
	~Baese()
	{
		cout << "Baese的析构函数" << endl;
	}
};

class Son:public Baese
{
public:
	Son()
	{
		cout << "Son的构造函数" << endl;
	}
	~Son()
	{
		cout << "Son的析构函数" << endl;
	}
	
};


void test01()
{
	Baese b;

	//Son s;
}
int main()
{
	
	test01();

	system("pause");
	return 0;
}