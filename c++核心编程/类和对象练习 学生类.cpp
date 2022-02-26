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

	//属性
	string m_Name;//姓名
	int m_ID;//学号

	//行为
	//显示姓名和学号
	void showStudent()
	{
		cout << "姓名：" << m_Name << "学号：" << m_ID << endl;
	}
};
int main()
{
	//创建一个具体学生
	Student s1;
	//给s1对象 进行属性赋值
	s1.m_Name = "阿三";
	s1.m_ID = 1;

	//显示学生信息
	s1.showStudent();

	Student s2;
	s2.m_Name = "张三";
	s2.m_ID = 10;

	s2.showStudent();

	system("pause");
	return 0;
}