#pragma once
#include<iostream>
using namespace std;
#include<string>

#include"Worker.h"//包含头文件

class Boos :public Worker
{
public:

	//构造函数
	Boos(int id, string name, int did);
	
	//显示个人信息
	virtual void ShowInfo() ;

	//获取岗位名称
	virtual string GetDeptName();


};