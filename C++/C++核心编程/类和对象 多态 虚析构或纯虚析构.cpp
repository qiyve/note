#include<iostream>
using namespace std;
#include<string>

// 虚析构和出虚析构

class Animal
{
public:
	Animal()
	{
		cout << "Animal构造函数调用" << endl;
	}
	~Animal()
	{
		cout << "Animal的析构函数调用" << endl;
	}
	//纯虚函数
	virtual void speak() = 0;
	
};

class Cat :public Animal
{
public:
	//猫的构造函数
	Cat(string name)
	{
		cout << "Cat构造函数调用" << endl;
		m_Name = new string(name);
	}
	virtual void speak()
	{
		cout << *m_Name<<"小猫在说话" << endl;
	}

	~Cat()
	{
		
		if (m_Name != NULL)
		{
			cout << "Cat析构函数调用" << endl;
			delete m_Name;
			m_Name = NULL;
		}
	}

	string * m_Name;
};

void test01()
{
	Animal* animal = new Cat("Tom");
	animal->speak();
	delete animal;//释放
}
int main()
{

	test01();

	system("pause");
	return 0;
}