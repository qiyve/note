#include<iostream>
using namespace std;
#include<string>

//多态案例二  制作饮品

//创建抽象类基类
class AbstractDrinking
{
public:
	//煮水
	virtual void Boil() = 0;
	//冲泡
	virtual void Brew() = 0;
	//倒入杯中
	virtual void PourInCup() = 0;
	//加入辅料
	virtual void PutSomething() = 0;

	//制作饮品  顺序
	void MakeDrink()
	{
		Boil();
		Brew();
		PourInCup();
		PutSomething();
	}
};

//制作咖啡
class Coffee :public AbstractDrinking
{
public:
	//煮水
	virtual void Boil()
	{
		cout << "烧点开水" << endl;
	}
	//冲泡
	virtual void Brew()
	{
		cout << "冲泡咖啡" << endl;
	}
	//倒入杯中
	virtual void PourInCup()
	{
		cout << "倒入杯子" << endl;
	}
	//加入辅料
	virtual void PutSomething()
	{
		cout << "加入方糖和牛奶" << endl;
	}
};

//冲泡茶水
class Tea :public AbstractDrinking
{
public:
	//煮水
	virtual void Boil()
	{
		cout << "烧点开水" << endl;
	}
	//冲泡
	virtual void Brew()
	{
		cout << "冲泡茶叶" << endl;
	}
	//倒入杯中
	virtual void PourInCup()
	{
		cout << "倒入茶壶" << endl;
	}
	//加入辅料
	virtual void PutSomething()
	{
		cout << "加入红枣和枸杞" << endl;
	}
};

//制作函数
void doMake(AbstractDrinking * abs)
{
	abs->MakeDrink();

	delete abs;
}

void test01()
{
	//冲泡茶水
	doMake(new Tea);

	cout << "----————————" << endl;
   // 制作咖啡
	doMake(new Coffee);
}
int main()
{

	test01();

	system("pause");
	return 0;
}