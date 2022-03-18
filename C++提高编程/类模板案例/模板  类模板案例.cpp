#include<iostream>
using namespace std;
#include"MyArray.hpp"


void printIntArray(MyArray<int> &arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr[i] << endl;
	}
}


void test01()
{
	MyArray<int> arr1(5);

	for (int i = 0; i < 5; i++)
	{
		//利用尾插法向数组中插入数据
		arr1.Push_Back(i);
	}
	cout << "arr1的打印输出为：" << endl;

	printIntArray(arr1);

	cout << "arr1 的容量为：" << arr1.getCapacity() << endl;
	cout << "arr1 的大小为：" << arr1.getSize() << endl;

	MyArray<int>arr2(arr1);

	cout << "arr2 的打印输出" << endl;

	printIntArray(arr2);

	//尾删
	arr2.Pop_Back();

	cout << "arr2 尾删后：" << endl;
	cout << "arr2 的容量为：" << arr2.getCapacity() << endl;
	cout << "arr2 的大小为：" << arr2.getSize() << endl;

	//MyArray<int>arr2(arr1);

	//MyArray<int>arr3(100);
	//arr3 = arr1;
}

//测试自定义数据类型
class Person
{
public:

	Person() {};//默认构造

	//有参构造
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

void printPerson(MyArray<Person>&arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << "姓名：" << arr[i].m_Name << " 年龄：" << arr[i].m_Age << endl;
	}
}
void test02()
{
	MyArray<Person>arr(10);

	Person p1("阿三", 15);
	Person p2("老王", 45);
	Person p3("大妈", 42);
	Person p4("保安", 40);

	//将数据插入到数组中
	arr.Push_Back(p1);
	arr.Push_Back(p2);
	arr.Push_Back(p3);
	arr.Push_Back(p4);

	//打印输出
	printPerson(arr);

	//输出容量
	cout << "Person 的容量：" << arr.getCapacity() << endl;
	//输出大小
	cout << "Person的大小" << arr.getSize() << endl;
}


int main()
{

	//test01();

	test02();

	system("pause");
	return 0;
}