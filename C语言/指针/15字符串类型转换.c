#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

int main01()
{
	//atoi()会扫描nptr字符串，跳过前面的空字符，直到遇到数字或正负号才开始做转换，
	//	而遇到数字或字符串结束符（'\0'）才结束转换，并将结果返回

	char ch[] = "  -12345-6";
	int i = atoi(ch);

	printf("%d\n", i);

	return 0;
}

int main02()
{

	char ch[] = "  -12.345-6";
	double i = atof(ch);

	printf("%.2f\n", i);

	return 0;
}

int main()
{
	char ch[] = "   125488- 6123";
	long i = atol(ch);

	printf("%ld\n", i);

	return 0;
}