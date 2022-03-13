#pragma once
#pragma once
#include<iostream>
using namespace std;
#include<string>

// 创建职工抽象类
// 职工的分类为：普通员工 、 经理 、老板
// 将三种职工抽象到一个类 （worker）中，；利用多态管理不同职工种类
// 职工的属性为： 职工编号  职工姓名  职工所在部门编号
// 职工的行为为： 岗位职工信息描述，获取岗位名称

//职工抽象类
class Worker
{
public:

	//展示个人信息
	virtual void ShowInfo() = 0;

	//获取岗位名称
	virtual string GetDeptName() = 0;

	//职工编号
	int m_Id;
	//职工姓名
	string m_Name;
	//部门编号
	int m_DeptID;

};