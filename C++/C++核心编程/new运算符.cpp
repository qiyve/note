#include<iostream>
using namespace std;

//1、new的基本语法
int *func()
{
	//在堆区创建一个整形数据
	//new返回的是 该数据类型的指针
	int*p=new int(10);
	return p;
}

void test01()
{
	int* p = func();

	cout << *p << endl;
	cout << *p << endl;
	cout << *p << endl;

	//堆区的数据 由程序员管理开辟，程序员管理释放
	//如果想释放堆区的数据，利用关键字 delete 
	delete p;

	//cout << *p << endl; //内存已经被释放，再次访问就是非法操作，会报错
}
//2、在堆区利用new开辟数组
void test02()
{
	//创建10个整形的数组，在堆区.   创建数组要用 []
	int* arr = new int [10]; //[10]代表数组中有10个元素

	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 10;//给10个元素赋值 10~19
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}

   //释放堆区数组
	//释放数组的时候要加[]才可以
	delete []arr; 
}

int main()
{
	//整形
	test01();

	//数组
	test02();


	system("pause");
	return 0;
}