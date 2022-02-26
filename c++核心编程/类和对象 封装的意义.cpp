#include<iostream>
using namespace std;

//圆周率
const double PI = 3.14;

//设计一个圆类，求圆的周长
//圆求周长的公式 ：2 * PI * 半径

//class 代表设计一个类，类后面紧跟着的就是类名称
class Yuan
{
	//访问权限
	//公共权限
public:

	//属性
	//半径
	int m_r;

	//行为
	//获取圆的周长
	double calculateZC()
	{
		return 2 * PI * m_r;
	}
};
int main()
{
	//通过这个圆类，创建一个具体的圆(对象)
	//实例化 （通过一个类 创建一个对象的过程）
	Yuan y1;
	//给圆对象 的属性赋值
	y1.m_r = 10;

	// 2 * PI *10 = 62.8
	cout << "圆的周长为：" << y1.calculateZC() << endl;


	system("pause");
	return 0;
}