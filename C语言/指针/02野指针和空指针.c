#include <stdio.h>


int main01()
{
	//不建议直接将一个变量的值直接复制给指针
	//野指针 ->  指针变量指向一个未知的空间
	int* p = 100;//程序中允许存在野指针
	//操作系统将0-255作为系统占用不允许访问操作
	//操作野指针对应的内存空间可能报错
	printf("%d\n", *p);


	system("pause");
	return 0;
}

int main()
{
	//空指针是指内存编号为0的空间
	int* p = NULL;
	*p = 300;
	printf("%d\n", *p);


	system("pause");
	return 0;
}