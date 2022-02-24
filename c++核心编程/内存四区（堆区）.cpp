#include<iostream>
using namespace std;


int *func()
{
	///利用关键字new，可以将数据开辟到堆区
	//指针 本质也是局部变量，放在栈上，指针保存的数据是放在堆区

	int* p = new int(100);//new int（100）返回的是堆区创建的地址，然后用指针去接收

	return p;
}
int main()
{

	//在堆区开辟数据
	int* p = func();
	cout << *p << endl;
	cout << *p << endl;



	system("pause");
	return 0;
}