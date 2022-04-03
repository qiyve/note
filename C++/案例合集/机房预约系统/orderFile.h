#pragma once
#include<iostream>
using namespace std;
#include<map>
#include"globalFile.h"
#include<fstream>
#include<string>

class OrderFile
{
public:

	//构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();

	//记录所有预约信息容器  key记录条数   value 具体记录的键值对信息
	map<int, map<string, string>>m_orderData;

	//预约记录条数
	int m_Size;

};
