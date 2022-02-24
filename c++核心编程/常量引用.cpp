#include<iostream>
using namespace std;

//打印输出  引用方式传递 可以修饰实参
//加上 const 变成常量引用  防止误操作
void showValue(const int& val)
{
	//val = 1000;   加上const 之后变为只读，不可以修改

	cout << "val= " << val << endl;
}

int main()
{
	//常量引用
	//使用场景： 用来修饰形参， 防止误操作
	
	int b = 10;

	//加上 const之后，编译器将代码修改 int temp = 10; const int & ret= temp;
	const int &ret = 10;//引用必须引一块合法的内存空

	//ret = 20;//加上const 之后变为只读，不可以修改


	//函数中利用常量引用防止误操作修改实参
	int a = 10;

	showValue(a);
	cout << "a= " << a << endl;


	system("pause");
	return 0;

}