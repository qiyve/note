//#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	
#pragma warning (disable:4996)

int main(void)
{
	//整型变量
	int a = 10;
	//短整型
	short b = 20;

	//长整型
	long c = 30;
	//长长整形
	long long d = 40;

	printf("%d\n", a);
	//占位符 %hd 表示输出一个短整型
	printf("%hd\n", b);
	//占位符 %ld 表示输出一个长整型
	printf("%ld\n", c);
	//占位符%lld 表示输出一个长长整型
	printf("%lld\n", d);

	//sizeof 计算数据类型在内存中占的字节（BYTE）大小
	//sizeof(数据类型)  sizeof(变量名)  sizeof 变量名
	unsigned int len = sizeof(int);

	//printf("%d\n", len);
	printf("整形：%d\n", sizeof(a));
	printf("短整形：%d\n", sizeof(b));
	printf("长整形： % d\n", sizeof(c));
	printf("长长整形：%d\n", sizeof(d));

	return 0;
}

