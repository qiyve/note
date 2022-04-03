#include<iostream>
using namespace std;
#include<string>

//分别利用普通写法和多态技术实现计算器

//普通写法
class Calculator
{
public:

	int getResult(string oper)
	{
		if (oper == "+")
		{
			return m_num1 + m_num2;
		}
		else if (oper == "-")
		{
			return m_num1 - m_num2;
		}

		else if (oper == "*")
		{
			return m_num1 * m_num2;
		}
		return 0;
	}
	//如果想要扩展新的功能，需要修改源码
	//在真实开发中，提倡 开闭原则
	//开闭原则 ：对扩展进行开发，对修改进行关闭

	int m_num1;//操作数1
	int m_num2;//操作数2
};

void test01()
{
	//创建计算器的对象
	Calculator c;
	c.m_num1 = 100;
	c.m_num2 = 100;
	//加法
	cout << c.m_num1 << "+" << c.m_num2 << "=" << c.getResult("+") << endl;
	//减法
	cout << c.m_num1 << "-" << c.m_num2 << "=" << c.getResult("-") << endl;
	//乘法
	cout << c.m_num1 << "*" << c.m_num2 << "=" << c.getResult("*") << endl;
}

//利用多态实现计算器

//实现计算机抽象类
class AbstractCalculator
{
public:

	virtual int getResult()
	{
		return 0;
	}

	int m_num1;
	int m_num2;
};

//加法加法计算器类
class AddCalculator :public AbstractCalculator
{
	//子类 virtual 可写可不写
	virtual int getResult()
	{
		return m_num1 + m_num2;
	}
};

//创建减法计算器类
class SubCalculator :public AbstractCalculator
{
	virtual int getResult()
	{
		return m_num1 - m_num2;
	}
};

//乘法计算器类
class MulCalculator :public AbstractCalculator
{
	virtual int getResult()
	{
		return m_num1 * m_num2;;
	}
};

void test02()
{
	//多态使用条件
	//父类指针或者引用指向子类对象

	//加法运算
	AbstractCalculator* abc = new AddCalculator;
	abc->m_num1 = 30;
	abc->m_num2 = 20;

	cout << abc->m_num1 << "+" << abc->m_num2 << "=" << abc->getResult() << endl;
	//用完后记得销毁
	delete abc;

	//减法运算
	abc = new SubCalculator;
	abc->m_num1 = 30;
	abc->m_num2 = 20;

	cout << abc->m_num1 << "-" << abc->m_num2 << "=" << abc->getResult() << endl;
	delete abc;

	//乘法运算
	abc = new MulCalculator;
	abc->m_num1 = 30;
	abc->m_num2 = 20;

	cout << abc->m_num1 << "*" << abc->m_num2 << "=" << abc->getResult() << endl;
	delete abc;


}
int main()
{

	//test01();

	test02();


	system("pause");
	return 0;
}