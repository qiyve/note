#include<iostream>
using namespace std;
#include<functional> //内建函数对象头文件

//内建函数对象 算术仿函数


//template <class T> T plus<T>       //加法仿函数
//template <class T> T minus<T>      //减法仿函数
//template <class T> T multiplies<T> //乘法仿函数
//template <class T> T divides<T>    //除法仿函数
//xtemplate <class T> T modulus<T>   //取模仿函数
//template <class T> T negate<T>     //取反仿函数

//negate 是一元运算  取反仿函数
void test01()
{
	negate<int>n;

	cout << n(20) << endl;

}

void test02()
{
	plus<int>p;

	cout << p(10, 10) << endl;
}

int main()
{
	test01();
	test02();

	system("pause");
	return 0;
}