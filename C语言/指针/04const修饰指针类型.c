#include <stdio.h>



int main01()
{
	//常量
	const int a = 10;
	//a = 100;// 错
	//指针间接修改常量的值
	int* p = &a;
	*p = 100;
	printf("%d\n", a);

	system("pause");
	return 0;
}

int main02()
{
	int a = 10;
	int b = 20;

	// const int* p = &a;  const 修饰指针类型
	// 可以修改指针变量的值（指针指向），不可以修改指针指向内存空间的值（指针指向的值）
	const int* p = &a;
	
	//p = &b; //ok
	//*p = 100;错

	printf("%d\n", *p);

	system("pause");
	return 0;
}

int main03()
{
	int a = 10;
	int b = 20;

	//int* const p = &a   const修饰指针变量
	// 可以修改指针指向内存空间的值（指针指向的值），不可以修改指针变量的值（指针指向）
	int* const p = &a;
	//p = &b; 错
	*p = 200;
	printf("%d\n", a);

	system("pause");
	return 0;
}

int main()
{
	int a = 10;
	int b = 20;
	//const int* const p = &a; 既修饰指针类型 又修饰指针变量
	const int* const p = &a;
	//可以利用二级指针来间接修改
	int** p1 = &p;
	//*p1 = &b;
	**p1 = 100;
	printf("%d\n", *p);

	//p = &b; 错误
	//*p = 100; 错误

	system("pause");
	return 0;
}