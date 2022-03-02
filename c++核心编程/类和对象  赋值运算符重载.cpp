#include<iostream>
using namespace std;

//赋值运算符重载

//创建一个自定义整形
class Person
{

public:
	
	Person(int age)
	{
		m_Age=new int(age);
	}

	~Person()
	{
		 //判断堆区m_Age 不为空 ，就释放它
		if (m_Age != NULL)
		{
			delete m_Age;
			m_Age = NULL;
		}
	}

	//重载赋值运算符
	Person &operator=(Person &p)
	{
		//编译器提供的是浅拷贝
		//m_Age = p.m_Age;

		//应该先判断是否有属性在堆区 如果有先释放干净 然后在深拷贝
		if (m_Age != NULL)
		{
			delete m_Age;
			m_Age = NULL;
		}
		//深拷贝
		m_Age = new int(*p.m_Age);//参数是引用 所以需要*解引用

		//返回对象本身
		return *this;
	}

	int* m_Age;
};

void test01()
{
	Person p1(18);

	Person p2(20);

	Person p3(30);
	p3 = p2 = p1;//赋值运算的操作

	cout << "p1的年龄为：" << *p1.m_Age << endl;// 利用* 解引用

	cout << "p2的年龄为：" << *p2.m_Age << endl;

	cout << "p3的年龄为：" << *p3.m_Age << endl;
}

int main()
{
	test01();

	/*int a = 10;
	int b = 22;
	int c = 15;

	c = b = a;

	cout << "a= " << a << endl;
	cout << "b= " << b << endl;
	cout << "c= " << c << endl;*/

	system("pause");
	return 0;
}