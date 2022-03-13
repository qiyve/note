#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

//创建经理类类


class Manager : public Worker
{
public:

	//构造函数
	Manager(int id, string name, int did);

	//展示个人信息
	virtual void ShowInfo();  //这里不能 = 0 ；抽象类无法实例化对象

	//获取员工岗位名称
	virtual string  GetDeptName();
};
