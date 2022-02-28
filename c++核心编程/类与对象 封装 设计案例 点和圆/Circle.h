#pragma once    //防止头文件重复包含
#include<iostream>
using namespace std;
#include"Point（点类）.h"

//圆类
class Circle
{
public:
	//设置半径
	void setR(int r);

	//获取半径
	int getR();

	//设置圆心
	void setCenter(Point center);

	//获取圆心
	Point getCenter();

private:

	int m_R;//半径

	//在类中可以让另一个类 作为本类中成员
	Point m_Center;//圆心
};