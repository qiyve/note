#include<iostream>
using namespace std;


// 深拷贝与浅拷贝
//浅拷贝： 简单的复制拷贝操作
//深拷贝： 在堆区重新申请空间，进行拷贝操作

class Person
{
public:
	Person() //默认构造
	{
		cout << "Person默认函数调用" << endl;
	}

	Person(int a,int height)//有参构造
	{
		m_Age = a;
		m_Height = new int(height);//开辟堆区空间

		cout << "Person有参构造函数的调用" << endl;
		
	}

	Person(const Person& p)//拷贝构造
	{	
		cout << "Person拷贝构造函数的调用" << endl;

		m_Age = p.m_Age;
		//m_Height = p.m_Height;编译器默认实现就是这行代码

		//深拷贝操作
		m_Height = new int(*p.m_Height);
	}

	~Person()
	{
		//析构代码，将堆区开辟数据做释放操作
		if (m_Height != NULL)
		{
			delete m_Height;
			m_Height = NULL;
		}
		cout << "Person的析构函数的调用" << endl;
	}
	int m_Age;//年龄
  // 利用 * 接收
	int* m_Height;//身高 
};

void test01()
{
	Person p1(18,160);

	cout << "p1的年龄：" << p1.m_Age <<"身高："<<*p1.m_Height<< endl;

	Person p2(p1);

	cout << "p2的年龄：" << p2.m_Age << "身高：" << *p2.m_Height << endl;
}
//浅拷贝带来的问题就是堆区的内存重复释放
//浅拷贝的内存 要利用深拷贝进行解决
int main()
{
	
	test01();

	system("pause");
	return 0;
}