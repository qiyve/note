
#include <iostream>
using namespace std;

//函数的声明   ：提前告诉编译器函数的存在
//比较函数 实现两个整形数字进行比较，返回较大的值
//声明可以多次 但是定义只能有一次

//函数声明
int max(int a, int b);



int main()
{
   //调用函数

	int a = 20;
	int b = 30;
	
	cout << max(a,b) << endl;

	system("pause");
		return 0;
}
//定义
int max(int a, int b)
{
	//三木运算符
	return a > b ? a : b;
}
