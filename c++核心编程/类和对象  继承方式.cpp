#include<iostream>
using namespace std;
#include<string>

//继承方式

//公共继承
class Baese1
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son1 :public Baese1
{
public:

	void func()
	{
		m_A = 10;// 父类中的公共权限成员  到子类中依然是公共权限 
		m_B = 10;// 父类中的保护权限成员  到子类中依然是保护权限
		//m_C = 10;// 父类中的私有权向成员  子类访问不到
	}
};

void test01()
{
	Son1 s1;
	s1.m_A = 100;
	//s1.m_B = 100;//到Son1中 m_B 是保护权限 类外访问不到
}

//保护继承
class Baese2
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son2 :protected Baese2
{
protected:
	void func()
	{
		m_A = 10;// 父类中的公共权限成员 到子类中变为保护权限
		m_B = 10;// 父类中的保护权限成员 到子类中依然是保护权限
      //m_C = 10;// 父类中的私有权向成员 子类访问不到
	}
};

void test02()
{
	Son2 s2;
	//s2.m_A = 100;//到 son2 中父类的公共权限成员 变为保护权限 类外访问不到
	//s2.m_B = 100; 
}

//私有继承
class Baese3
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son3:private Baese3
{
private:

	void func()
	{
		m_A = 10;//父类中的公共权限成员 到子类变为私有权限
		m_B = 10;//父类中的保护权限成员 到子类变为私有权限
		//m_C = 10;//父类中的私有权限成员 子类访问不到
	}
};

void test03()
{
	Son3 s3;
	//s3.m_A = 100;//到 Son3中 父类中的公共权限成员 变为私有权限 类外访问不到
	//s3.m_B = 100;//
}

int main()
{
	
	

	system("pause");
	return 0;
}