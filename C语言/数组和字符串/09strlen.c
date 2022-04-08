#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>


int main01()
{
	//计算字符有效个数

	char ch[] = "hello world";
	printf("数组大小：%d\n",sizeof(ch));
	printf("字符串长度：%d", strlen(ch));

	system("pause");
	return 0;
}

int main()
{
	char ch[] = "hello world";
	int len = 0;

	while (ch[len]!='\0')
	{
		len++;
	}

	printf("字符串长度：%d", len);

	system("pause");
	return 0;
}