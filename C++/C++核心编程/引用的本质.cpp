#include<iostream>
using namespace std;

//引用的本质
//引用的 本质就是一个指针常量
//引用一旦初始化后，就不可以发生改变

//发现是引用，转换成 int * const ret = &a；
void func(int& ret)
{
	ret = 100; //ret 是引用，转换成 * ret = 100；
}

int main()
{
	int a = 10;

	/*自动转换成 int* const ret = &a ；指针常量是指针 指向不可改，
	也说明为什么引用不可更改 */
	int& ret = a;

	ret = 20;//内部发现是 ret 是引用 自动转换成 * ret = 20；

	cout << "a= " << a << endl;
	cout << "ret= " << ret << endl;



	system("pause");
	return 0;
}