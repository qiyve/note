#include<iostream>
using namespace std;
#include<string>

//类做友元


class Building;//声明，

class GoodGay
{
public:

	GoodGay();


	void visit();//参观函数  访问Building中的属性

	Building* building;
};

class Building
{

	friend class GoodGay;

public:
	Building();

public:

	string m_SittingRoom;//客厅

private:

	string m_BedRoom;//卧室

};

//类外写成员函数
Building::Building()//利用作用域
{
	m_SittingRoom = "客厅";
	m_BedRoom = "卧室";
}

GoodGay::GoodGay()
{
	//创建建筑物对象
	building = new Building;

}

void GoodGay::visit()
{
	cout << "好朋友 正在访问：" << building->m_SittingRoom << endl;
	cout << "好朋友 正在访问：" << building->m_BedRoom << endl;
}
void test01()
{
	GoodGay gg;
	gg.visit();
	
}
int main()
{
	
	test01();

	system("pause");
	return 0;
}