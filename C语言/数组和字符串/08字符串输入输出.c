#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>


int main01()
{
	char ch[100];

	//通过键盘获取字符串
	//gets接受字符串可以带空格
	gets(ch);
	//通过正则表达式 获取带空格字符串
	//scanf("%[^\n]", ch); 

	printf("%s\n", ch);

	system("pause");
	return 0;
}

int main02()
{
   //fgets（）
	char ch[10];
	//"hello \n\0" 
	//fgets 可以接收空格
	//fgets获取字符串少于元素个数有\n  大于等于 没有\n
	fgets(ch,sizeof(ch),stdin); //stdin 系统提供的指针

	printf("%s\n", ch);

	system("pause");
	return 0;
}

//输出 puts()
int main04()
{
	char ch[] = "hello world";

	//puts 自带换行
	//puts(ch);
	//puts 遇到 \0结束
	puts("hello \0 world");
	//puts("");  换行

	system("pause");
	return 0;
}

//输出 fputs
int main()
{
	char ch[] = "hello world";

	//int fputs(const* str, FILE * stream) stream 文件指针 固定写stdout
	fputs(ch, stdout);

	system("pause");
	return 0;
}