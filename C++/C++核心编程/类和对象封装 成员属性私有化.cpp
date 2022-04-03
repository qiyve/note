#include<iostream>
using namespace std;
#include<string>

//成员属性设置为私有
//1、可以自己控制读写权限
//2、对于写权限，我们可以检测数据的有效性

//设计人类
class Person
{
public:

	//设置姓名  可读可写
	void setName(string name)
	{
		m_Name = name;
	}
	//获取姓名
	string getName()
	{
		return m_Name;
	}

	//获取年龄  只读 
	int getAge()
	{
		//m_Age = 0;//初始换为0岁 
		return m_Age;
	}
	//设置年龄 
	void setAge(int age)
	{
		if (age < 0 || age>150)
		{
			m_Age = 0;
			cout << "你这个老妖精" << endl;

			return;
		}
		m_Age = age;
	
	}
	//设置情人 只写
	void setLover(string lover)
	{
		m_Lover = lover;
	}
private:
    //姓名  可读可写
	string m_Name;

	//年龄  只读
	int m_Age;

	//情人  只写
	string m_Lover;

};
int main()
{
   //创建具体对象
	Person p;

	//设置姓名 可读可写
	p.setName ("张三");

	cout << "姓名为:" << p.getName() << endl;
	
	//设置年龄  只读
	//p.m_Age = 18;// 错误 
	//p.m_Age(18);// 错误  
	cout << "年龄为;" << p.getAge() << endl;

	//设置年龄  可读可写
	p.setAge (100);
	cout << "年龄为;" << p.getAge() << endl;
	
    //设置情人  只写
	p.setLover("阿三");
	//cout << "情人姓名 ：" << p.setLover << endl;//是只写权限


	system("pause");
	return 0;
}