#include<iostream>
using namespace std;



int main()
{
	//引用的注意事项
	//1. 引用必须初始化
	
	int a = 10;
	//int& b;  // 错误， 必须初始化
	
	//2. 引用在初始化后，不可以改变

	int& b = a;// 一旦开始引用就不可以更改
	int c = 100;

	b = c;//这是赋值操作，不是更改引用 

	
	
	cout << "a= " << a << endl;
	cout << "b= " << b << endl;
	cout << "c= " << c << endl;
	
		

	
	system("pause");
	return 0;
}