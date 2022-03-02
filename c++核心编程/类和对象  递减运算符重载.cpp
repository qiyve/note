#include<iostream>
using namespace std;

//重载递减运算符

//创建一个自定义整形
class MyInteger
{

	//利用友元访问私有属性 关键字 friend
	friend ostream& operator<<(ostream& cout, MyInteger mayint); 

public:
	MyInteger()
	{
		m_Num = 2;
	}

	//前置递减 --运算符
	MyInteger& operator--()
	{
		m_Num--;
		return *this;
	}
	//后置递减--运算符
	MyInteger operator--(int)//int 占位参数 区分前后递减
	{
		//先记录当前结果
		MyInteger temp;
		//后 递减
		m_Num--;
		//返回记录结果
		return temp;
	}
private:

	int m_Num;
};

//重载<<运算符
ostream& operator<<(ostream& cout, MyInteger mayint)
{
	cout << mayint.m_Num;
	return cout;
}

//前置递减
void test01()
{
	MyInteger myint;

	cout <<-- myint << endl;
	cout << myint << endl;
}

//后置递减  先返回结果 然后在做 - 1 操作
void test02()
{
	MyInteger myint;

	cout << myint-- << endl;
	cout << myint << endl;

}

int main()
{
	//test01();

	test02();


	system("pause");
	return 0;
}