#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main01()
{
	
	int a = 10;
	int c = 123456;

	// 默认为右对齐  左对齐 利用 -
	printf("===%-5d===\n", a);
	// m(代表一个整数)   数据最小宽度
	// 0数字0          将输出的前面补上0直到沾满指定列宽为止不可以搭配使用 -
	printf("===%05d===\n", a);
	printf("===%05d===\n", c);//如果大于指定宽度 正常输出

	/*m.n(代表整数) m指域宽，对应输出设备上所占字符数，n指精度，说明输出的实型数的小数位数，
	 对数值型来说，未指定n时，隐含的精度为 n=6位 */

	float b = 3.14;
	printf("===%-7.2f===",b); //不建议用0补充

	return 0;
}

int main()
{
	char ch = 'a';

	//printf("%c\n", ch);
	//输出字符
	//putchar(ch);
	//putchar('B');
	//putchar(97);
	putchar('\n');


	return 0;
}