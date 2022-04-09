#include <stdio.h>

int main01()
{
	int a = 0xaabbccdd;
	//a = 100;
	printf("%p\n", &a);
	

	system("pause");
	return 0;
}
int main02()
{
	//定义指针变量存储变量地址
	int a = 10;
	//指针类型  -> 数据类型* 
	int* p;
	p = &a;
	//通过指针间接改变变量的值
	*p = 100;
	printf("%p\n", p);
	printf("%p\n", &a);

	printf("%d\n", a);
	printf("%d\n", *p);
	
	system("pause");
	return 0;
}

int main03()
{
	//&是取地址符号是升维度的
	//*是取值符号是降维度的

	char ch = 'a';
	char* p = &ch;
	//printf("%d\n", sizeof(char*));
	//int a = 10;
	//int* p = &a;
	//printf("%d\n", sizeof(int*));

	//指针在内存中占的字节大小
	//在32为操作系统下所有指针类型是4个字节大小
	//在64为操作系统下所有指针类型是8个字节大小
	printf("%d\n", sizeof(char*));
	printf("%d\n", sizeof(int*)); 
	printf("%d\n", sizeof(short*));
	printf("%d\n", sizeof(long*));
	printf("%d\n", sizeof(long long*));
	printf("%d\n", sizeof(float*));
	printf("%d\n", sizeof(double*));

	system("pause");
	return 0;
}

int main()
{
	//在定义指针类型一定要和变量的类型对应上
	char ch = 97;

	int* p = &ch;
	//*p = 123;

	printf("%d\n", *p);
	printf("%d\n", ch);


	/*printf("%p\n", p);
	printf("%p\n", &ch);*/


	system("pause");
	return 0;
}