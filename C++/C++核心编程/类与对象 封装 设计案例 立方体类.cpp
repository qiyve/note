#include<iostream>
using namespace std;

//设计案例 立方体
//1、创建 立方体类
//2、设计属性
//3、设计行为
//4、分别利用全局函数和成员函数判断两个立方体是否相等


class Cube
{
	//权限
public://公共权限

	//行为
	// 设置获取它的长宽高

	//设置长
	void setL(int l)
	{
		m_L= l;
	}

	//获取长
	int getL()
	{
		return m_L;
	}
	//设置宽
	void setW(int w)
	{
		m_W = w;
	}
	//获取宽
	int getW()
	{
		return m_W;
	}
	//设置高
	void setH(int h)
	{
		m_H = h;
	}
	//获取高
	int getH()
	{
		return m_H;
	}
	//获取立方体的面积 : 2 *长*高 + 2* 长*宽 + 2 * 宽*高
	int calculateS()
	{
		return 2 * m_L * m_W + 2 * m_L * m_H + 2 * m_W * m_H;
	}
	//获取立方体的体积 ：长 * 宽 * 高
	int calculateV()
	{
		return m_L * m_W * m_H;
	}

	//利用成员函数 判断两个立方体是否相等
	bool isSameByClass(Cube&c)
	{
		if (m_L == c.getL() && m_W == c.getW() && m_H == c.getH())
		{
			return true;
		}
		return false;
	}

private://私有权限

	//属性
	int m_L;//长

	int m_W;//宽

	int m_H;//高
};

//4、利用全局函数 判断两个立方体是否相等
bool isSame(Cube &c1,Cube &c2)
{
	if (c1.getL() == c2.getL() && c1.getW() == c2.getW() && c1.getH() == c2.getH())
	{
		return true;
	}
	return false;
}
int main()
{
	//创建立方体对象
	Cube c1;

	//给长宽高赋值
	c1.setL(10);
	c1.setW(10);
	c1.setH(10);

	cout << "立方体的面积为：" << c1.calculateS() << endl;
	cout << "立方体的体积为：" << c1.calculateV() << endl;

	//创建第二个立方体
	Cube c2;

	c2.setL(10);
	c2.setW(10);
	c2.setH(10);

	//利用全局函数 判断两个立方体是否相等
	bool ret=isSame(c1, c2);
	if(ret)
	{ 
		cout << "c1和c2是相等的" << endl;
	}
	else
	{
		cout << "c1和c2是不相等的" << endl;
	}
	//利用成员函数 判断两个立方体是否相等
	ret = c1.isSameByClass(c2);
	if (ret)
	{
		cout << "成员函数，c1和c2是相等的" << endl;
	}
	else
	{
		cout << "成员函数，c1和c2是不相等的" << endl;
	}

	system("pause");
	return 0;
}

