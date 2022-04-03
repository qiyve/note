#include<iostream>
using namespace std;

//交换函数 //1、值传递
void mySwap01(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;

	//cout << "mySwap01中a= " << a << endl;
	//cout << "mySwap01中b= " << b << endl;
}

//2、地址传递
void mySwap02(int *a, int*b)
{

	int temp = *a;
	*a = *b;
	*b= temp;
}


//3、引用传递
void mySwap03(int& a, int& b)
{

	int temp = a;
	a = b;
	b = temp;
 }



int main()
{
	int a = 10;
	int b = 50;

	
	mySwap01(a, b);//值传递  形参不会修饰实参

	
	mySwap02(&a, &b);//地址传递 形参会修饰实参

	mySwap03(a, b); //引用传递，形参会修饰实参


	cout << "a= " << a << endl;
	cout << "b= " << b << endl;
	
	//总结： 通过引用参数产生的效果同地址传递是一样的，引用的语法更清楚简单
	
	system("pause");
	return 0;
}