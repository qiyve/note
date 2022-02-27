#include<iostream>
using namespace std;
#include<string>


//设计一个学生类，属性：姓名 ，和学号
// 可以给姓名和学号赋值，可以显示学生的姓名和学号


//学生类
//class 代表设计一个类，类后面紧跟着的就是类名称
class Student
{
	//访问权限
public://公共权限

	//类中的属性和行为，我们统一称为 成员
	//属性  成员属性  成员变量
	//行为  成员函数  成员方法


	//属性
	string m_Name;//姓名
	int m_ID;//学号

	//行为
	//显示姓名和学号
	void showStudent()
	{
		cout << "姓名：" << m_Name << "学号：" << m_ID << endl;
	}
	//给姓名赋值
	void setName(string name)
	{
		m_Name = name;
	}
	//给学号赋值
	void setID(int id)
	{
		m_ID = id;
	}
};
int main()
{
	//创建一个具体学生
	Student s1;
	//给s1对象 进行属性赋值
	
	//s1.m_Name = "阿三";
	s1.setName("阿三");
	//s1.m_ID=1;
	s1.setID(1);

	//显示学生信息
	s1.showStudent();

	Student s2;
	s2.m_Name = "张三";
	s2.m_ID = 10;

	s2.showStudent();

	system("pause");
	return 0;
}