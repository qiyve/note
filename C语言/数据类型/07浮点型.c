#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	



int main01()
{

	float a = 3.14f;
	double b = 3.14;

	printf("%.2f\n", a);
	printf("%f\n", b);

	//sizeof 字节大小
	//浮点型数据 存储在内存中的格式分为：符号位 指数位 小数位
	printf("%d\n", sizeof(a));
	printf("%d\n", sizeof(b));

	return 0;
}

int main02()
{
	int a = 10;
	float b = 3.14;

	//占位符 %p 表示输出一个变量对应的内存地址编号（无符号十六进制整形） 
	printf("%p\n", &a);
	printf("%p\n", &b);

	//大小端对齐
	getchar();
	return 0;
}

int main()
{
	//科学计数法 e代表10 
	
	//float a = 3210.456; 
	//float a = 0.123452;
	//printf("%e\n", a);

	float b = 3.2e3f;
	printf("%f\n", b);

	return 0;
}