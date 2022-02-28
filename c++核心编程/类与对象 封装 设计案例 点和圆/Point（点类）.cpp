#include"Point（点类）.h"


void Point::setX(int x)// 作用域符号 ：：
{
	m_X = x;
}
//获取x
int Point::getX()
{
	return m_X;
}

//设置y
void Point::setY(int y)
{
	m_Y = y;
}
//获取y
int Point::getY()
{
	return m_Y;
}
