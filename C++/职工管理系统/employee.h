#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

//创建普通员工类
//普通员工类继承职工抽象类，并重写父类中纯虚函数
//在头文件和源文件的文件下分别创建 employee.h 和employee.cpp 文件 

class Employee : public Worker
{
public:

	//构造函数
	Employee(int id, string name, int did);

	//展示个人信息
	virtual void ShowInfo();

	//获取员工岗位名称
	virtual string  GetDeptName();
};
