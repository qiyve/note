#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main()
{
	//数据溢出
	/*当超过一个数据类型能够存放最大的范围时，数值会溢出。
	  有符号位最高位溢出的区别：符号位溢出会导致数的正负发生改变，
	  但最高位的溢出会导致最高位丢失*/
	char ch = 127;
	ch = ch + 2;
	printf("%d\n", ch);

	return 0;
}