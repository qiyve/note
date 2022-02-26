#include<iostream>
using namespace std;

//函数的占位参数
//语法  返回值类型 函数名 （数据类型）{ }

//目前阶段的占位参数，我们还用不到，后面课程中会用到
//占位参数，还可以有默认参数
void func(int a,int=10)
{
	cout << "this is func" << endl;
}
int main()
{
	func(10, );//占位参数必须填补

	system("pause");
	return 0;
}

