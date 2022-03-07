#include<iostream>
using namespace std;

//多态的基本概念

//动物类
class Animal
{
public:
   // 虚函数  关键字 vritual 
	virtual void speak()
	{
		cout << "动物在说话" << endl;
	}
};

//猫类
class Cat :public Animal
{
public:
	void speak()
	{
		cout << "小猫在说话" << endl;
	}
};

//狗类
class Dog:public Animal
{
public:

	void speak()
	{
		cout << "小狗在说话" << endl;
	}
};

//执行说话函数
//地址早绑定  在编译阶段确定函数地址
//如果想执行让猫说话，那么这个函数地址就不能提前绑定需要在运行阶段进行绑定， 地址晚绑定
void doSpeak(Animal &animal) // Animal & animal = cat;
{
	animal.speak();
}

void test01()
{
	Cat cat;
	doSpeak(cat);

	Dog dog;
	doSpeak(dog);
}
int main()
{

	test01();

	system("pause");
	return 0;
}