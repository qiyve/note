#include<iostream>
using namespace std;

//函数重载 注意事项
//1、引用作为重载的条件
void func(int& a) // int &a =10 不合法
{
	cout << "int &a 的调用" << endl;
}

void func(const int& a)  //const int &a =10 合法
{
	cout << "const int &a 的调用" << endl;
}

//2、函数重载碰到默认参数
void func02(int a,int b=10) 
{
	cout << "int a int b 的调用" << endl;
}
void func02(int a) 
{
	cout << "int a 的调用" << endl;
}

int main()
{ 
	//1、引用作为重载的条件
	int a = 10;
	func(a);//调用无sonst  可读可写

	
	func(10);//调用有 const  只读
	
  //2、函数重载碰到默认参数
  
	//func02(10); //当函数重载碰到默认参数，出现二义性（歧义），报错，尽量避免这种情况


	system("pause");
	return 0;
}

