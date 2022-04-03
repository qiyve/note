#include<iostream>
using namespace std;

//重载递增运算符

//自定义整形
class MyInteger
{    
	//利用友元关键字 允许访问私有属性
	friend ostream& operator<<(ostream& cout, MyInteger myint);

public:
	MyInteger()
	{
		m_Num = 0;
	}

	//重载前置++运算符  返回引用为了一直对一个数据进行递增操作
	MyInteger& operator++()
	{
		m_Num++;
		return *this;//this是指向自身，加*解引用 返回
	 }


	//重载后置++运算符
	//MyInteger operator++(int) 这个int代表占位参数可以用于区分前置和后置递增
	MyInteger operator++(int)
	{
		//先记录当时结果
		MyInteger temp;
		//后 递增
		m_Num++;
		//最后将记录的结果做返回
		return temp;
	}
private:

	int m_Num;
};


//重载<<运算符
ostream &operator<<(ostream &cout, MyInteger myint)
{
	cout << myint.m_Num;
	return cout;
}

//前置递增
void test01()
{
	MyInteger myint;

	cout << ++(++myint) << endl;//2

	cout << myint << endl;//2
}

//后置递增
void test02()
{
	MyInteger myint;

	cout << myint++<< endl;//0

	cout << myint << endl;//1
}
int main()
{
	test01();


	test02();

	//int a = 0;
	//cout << ++(++a) << endl;
	//cout << a << endl;


	system("pause");
	return 0;
}