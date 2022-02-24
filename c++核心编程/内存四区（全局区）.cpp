#include<iostream>
using namespace std;

//全局变量  ： 只要没写在函数体中的变量称作全局变量
int g_a = 10;
int g_b = 10;

//const 修饰的全局变量  全局常量

const int c_g_a = 10;
const int c_g_b = 10;

int main()
{
	//全局区
	
	//全局变量、 静态变量、常量


	//创建普通局部变量
	int a = 10;
	int b = 10;
	cout << "局部变量a的地址：" << (int)&a << endl;//加(int)强转成十进制
	cout << "局部变量b的地址：" << (int)&b << endl;

	//全局变量地址
	cout << "全局变量g_a的地址" << (int)&g_a << endl;
	cout << "全局变量g_b的地址" << (int)&g_b << endl;

	//静态变量   在普通变量前面加static，属于静态变量
	static int s_a = 10;
	static int s_b = 20;

	cout << "静态变量s_a的地址" << (int)&s_a << endl;
	cout << "静态变量s_b的地址" << (int)&s_b << endl;


	//常量
	//字符串常量
	
	cout << "hello world的地址" << (int)&"hello world" << endl;

	//const修饰的变量
	//const修饰的全局变量   const修饰的局部变量


	//const修饰的全局变量   全局常量

	cout << "全局常量c_g_a的地址" << (int)&c_g_a << endl;
	cout << "全局常量c_g_b的地址" << (int)&c_g_b << endl;


	//const修饰的局部变量   局部常量
	const int c_l_a = 10; //c-const  g-global(全局)   l-local（局部）
	const int c_l_b = 10;
	
	cout << "局部常量c_l_a地址" << (int)&c_l_a << endl;
	cout << "局部常量c_l_b地址" << (int)&c_l_b << endl;

	//c++中在程序运行前分为全局区和代码区
	// 代码区特点是共享和只读
	// 全局区中存放全局变量、静态变量、常量
	// 常量区中存放const修饰的全局常量和字符串常量


	system("pause");
	return 0;
}