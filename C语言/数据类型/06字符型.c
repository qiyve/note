#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main01(void)
{
	//字符型变量

	char ch = 'a';

	//打印字符型变量
	printf("%c\n", ch);
	//打印ch对应的十进制
	printf("%d\n", ch);

	// unsigned int len = sizeof(ch)
	printf("字符型大小：%d\n", sizeof(ch));

	return 0;
}

int main()
{
	/*char ch1 = 'a';
	char ch2 = 'A';
	printf("%d\n",ch1 - ch2);*/

	//小写字母转大写字母
	char ch;
	scanf("%c", &ch);

	printf("%c\n", ch-32);


	return 0;
}
