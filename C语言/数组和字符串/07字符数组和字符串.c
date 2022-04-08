#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>


int main01()
{
	//定义字符数组
	char arr[5] = { 'h','e','l','l','o' };
	//字符
	//char ch = 'a';
	//字符串 字符串结束标志为\0 数字0等同于\0  但是不等同‘0’
	//char* arr = "hello";
	//char arr[] = "hello";
	//char arr[] = { 'h','e','l','l','o','\0' };

	printf("%s", arr); //打印字符串

	//printf("%d\n",sizeof(arr));  //sizeof (数据类型)
	
	//for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	//{
	//	printf("%c", arr[i]);
	//}

	system("pause");
	return 0;
}

int main02()
{
	//定义字符数组存储字符串
	char ch[10];

	//注意：%s 接收空格前的内容
	scanf("%s", ch);

	printf("%s", ch);

	system("pause");
	return 0;
}
int main()
{
	//字符串拼接
	char ch1[] = "hello";
	char ch2[] = "world";
	char ch3[20];

	int i = 0; //下标
	int j = 0;

	while (ch1[i]!='\0')
	{
		ch3[i] = ch1[i];
		i++;
	}
	while (ch2[j]!='\0')
	{
		ch3[i + j] = ch2[j];
		j++;
	}

	ch3[i + j] = '\0';

	printf("%s", ch3);

	system("pause");
	return 0;
}