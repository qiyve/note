#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main01()
{
	/*char ch;

	scanf("%c", &ch);
	putchar(ch);*/
	
	int a, b;
	scanf("%d,%d", &a, &b);
	printf("%d\t%d", a, b);

	system("pause");
	return 0;
}

int main()
{

	char ch;

	//接收键盘 获取字符
	ch = getchar();
	putchar(ch);

	//暂时停留界面
	getchar();
	return 0;
}