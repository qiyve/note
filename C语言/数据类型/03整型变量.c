#include<stdio.h>

int main01(void)
{
	//数据类型 标识符 = 值
	//无符号  unsigned  有符号 signed
	signed int a = -10;

	//unsigned int a = 10;  
	//%u 占位符 表示输出一个无符号无符号十进制数据类型
	//printf("%u\n", a);

	printf("%d\n", a);
	return 0;
}

int main()
{
	//进制
    //二进制0-1  八进制0-7  十六进制0-9 10-15（a-f A-F)

	//int a = 10;
	//printf("%d\n", a);
	////占位符 %x 输出一个十六进制整形
	//printf("%x\n", a);
	//printf("%X\n", a);
	////占位符 %o 输出一个八进制整形
	//printf("%o\n", a);

	//定义八进制数据 以0开头
	int a = 0123;
	//定义十六进制数据 以0x开头
	int b = 0x123;
	//在计算机定义数据时 不可以直接定义二进制
	printf("%d\n", a);
	printf("%o\n", a);
	printf("%x\n", a);

	printf("%d\n", b);
	printf("%o\n", b);
	printf("%x\n", b);


	return 0;

}