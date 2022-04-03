#include<iostream>
using namespace std;
#include<string>

//成员函数做友元

//创建类
class Building;//声明，避免编译器报错

class GoodGay
{
public:

	GoodGay();

	void visit();//让visit 可以访问Building中的私有成员

	void visit2();// 让 visit2 不可以访问Building中的私有成员

	Building* building;

};

class Building
{
	//成员函数visit是Building好朋友 可以访问   加关键字 friend 
	friend void GoodGay::visit();

public:

	 Building();

public://公共
	 
	string m_SttingRoom;//客厅

private://私有

	string m_BedRoom;//卧室

};

//类外写成员函数
Building::Building()
{
	m_SttingRoom = "客厅";
	m_BedRoom = "卧室";
}

GoodGay::GoodGay()
{
	//创建建筑的对象
	building = new Building;
}

void GoodGay::visit()
{
	cout << "好基友visit 正在访问:" << building->m_SttingRoom << endl;
	cout << "好基友visit 正在访问：" << building->m_BedRoom << endl;
}

void GoodGay::visit2()
{
	cout << "阿三visit2 正在访问:" << building->m_SttingRoom << endl;

	// visit2 不是Building的好朋友 所以不饿可以访问
	cout << "阿三visit2 正在访问：" << building->m_BedRoom << endl;
}

//测试
void test01()
{
	GoodGay gg;
	//gg.visit();
	gg.visit2();
	
}
int main()
{
	
	test01();

	system("pause");
	return 0;
}