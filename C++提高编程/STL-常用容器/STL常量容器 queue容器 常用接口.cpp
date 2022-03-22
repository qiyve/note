#include<iostream>
using namespace std;
#include<queue>
#include<string>

//队列queue 容器 常用接口

//构造函数：
//queue<T>que;       //queue采用模板类实现，queue对象的默认构造形式
//queue（const queue& que）； //拷贝构造函数

//赋值操作：
//queue& operator= (const queue& que);  //重载等号运算符

//数据存取：
//push(elem);             //从队尾添加元素
//pop（）；               //从队头移除第一个元素
//back（）；              //返回最后一个元素
//front （）；             //返回第一个元素

//大小操作：
//emptm（）;             //判断堆栈是否为空
//size（）；                //返回栈的大小

class Person
{
public:

	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

void test01()
{
	//创建队列
	queue<Person>q;

	//准备数据
	Person p1("唐僧", 20);
	Person p2("孙悟空", 22);
	Person p3("猪八戒", 26);
	Person p4("沙和尚", 25);

	//入队
	q.push(p1);
	q.push(p2);
	q.push(p3);
	q.push(p4);

	cout << "队列大小位：" << q.size() << endl;

	//判断队列不为空，查看对头队尾，出队
	while (!q.empty())
	{
		//查看对头
		cout << "对头元素---姓名：" << q.front().m_Name << " 年龄：" << q.front().m_Age << endl;

		//查看队尾
		cout << "对尾元素---姓名：" << q.back().m_Name << " 年龄：" << q.back().m_Age << endl;

		//出队
		q.pop();
	}

	//查看大小
	cout << "队列的大小位：" << q.size() << endl;
}

//总结：  入队 --- push
//        出队 --- pop
//    返回队头 --- front
//    返回队尾 --- back
//判断是否为空 --- empty
//  返回栈大小 --- size()

int main()
{
	test01();
	

	system("pause");
	return 0;
}