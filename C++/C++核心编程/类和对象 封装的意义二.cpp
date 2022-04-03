#include<iostream>
using namespace std;
#include<string>

//访问权限
//三种
 
//公共权限   public     成员 类内可以访问  类外也可以访问
  
//保护权限   protected  成员 类内可以访问  类外不可以访问   儿子也可以访问父亲中的保护内容（继承中）
 
//私有权限   private    成员 类内可以访问  类外不可以访问   儿子不可以访问父亲的私有内容（继承中）

class Person
{
public:
	//公共权限
	string m_Name;//姓名

	
protected:
	//保护权限
	string m_Car;//汽车


private:
	//私有权向
	int m_Password;//银行卡密码


public:
	void func()
	{
		m_Name = "张三";
		m_Car = "拖拉机";
		m_Password = 123456;
	}

};
int main()
{
	
	//实例化具体对象
	Person p1;

	p1.m_Name = "阿三";
	//p1.m_Car = "大众";     // 保护权限内容，在类外访问不到
    //p1.m_Password = 123;   // 私有权限内容，在类外访问不到

	p1.func();

	//总结： 类内可以访问三个权限，类外不可以访问 保护和私有权限
	system("pause");
	return 0;
}