
#include <iostream>
using namespace std;

int main()
{
	// 1、const修饰指针  --常量指针
	
	int a = 10;
	int b = 20;

	const int* p = &a;
	
	//*p=20；  错误  指针指向可以修改，指针指向的值不可以修改
	p = &b; //正确

	// 2、const修饰常量  --指针常量 
	
	int* const p2 = &b;
	

	*p2 = 100;//正确
	//p2 = &a; 错误  指针指向不可以修改，指针指向的值可以修改
	
	// 3、const既修饰指针又修饰常量 
	const int* const p3 = &a;

	//指针的指向和指针指向的值都不可以修改

	//*p3 = 100;  错误
	//p3 = &b;    错误


	system("pause");
	return 0;
}
