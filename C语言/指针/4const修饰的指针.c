#include <stdio.h>


int main01()
{
	const int a = 10;
	//a = 100; err
	//通过一级指针间接修改变量的值
	int* p = &a;
	*p = 100;




	system("pause");
	return 0;
}

int main02()
{
	char ch1[] = "hello";
	char ch2[] = "world";

	//指向常量的指针
	//可以修改指针变量的值（指针de指向）， 不可以修改指针变量指向内存的值（指针指向的值）
	const char* p = ch1;
	// *p = 'm'; err
	//p[2] = 'm'; // *(p+2)= 'm' // err 
	//p = ch2;  //ok



	system("pause");
	return 0;
}

int main03()
{

	char ch1[] = "hello";
	char ch2[] = "world";

	//常量指针
	//可以修改指针变量指向内存空间的值（指针指向的值）
	//不可以修改指针变量的值 （指针的指向）
	char* const p = ch1;
	//p = ch2; err
	*p = 'w'; // ok  // ch[0]
	*(p + 2) = 'w';//ok 

	printf("%s\n", p);
	printf("%s\n", ch1);

	return 0;
}

int main()
{
	char ch1[] = "hello";
	char ch2[] = "world";

	//const既修饰指针指向 又修饰指针指向的值
	//指针的指向和指针指向值都不可以修改  只读
	const char* const p = ch1;

	// *p = ch2;  err
	// *p = 'w';  err

	char** p1 = &p;

	//*p1 = ch2;
	*(*p1 + 1) = 'm';

	printf("%s\n", p);

	return 0;
}