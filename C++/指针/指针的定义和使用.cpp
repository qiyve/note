
#include <iostream>
using namespace std;

int main()
{
//1、定义指针
	int a = 30;
	
	//创建指针 指针定义语法 数据类型 * 指针变量名
	int* p;
	 
	//利用指针记录a的地址
	p = &a;

	cout << "a的地址为 " << &a << endl;
	cout << "指针p为 " << p << endl;
 
//2、使用指针
	//可以通过解引用的方式来找到指针指向的内存
	//指针前面加 * 代表，找到指针指向的内存中的数据
	//可以通过指针变量来读取或修改内存中的数据
	 
	*p = 1000;

	cout << "a= " << a << endl;
	cout << "*p= " << *p << endl;



	system("pause");
		return 0;
}
