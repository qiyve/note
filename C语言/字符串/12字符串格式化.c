#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>


int main01()
{
	char ch[100];

	//sprintf 
	sprintf(ch, "hello world");
	sprintf(ch, "%d+%d=%d",1,2,3);
	sprintf(ch, "%02d+%02d=%02d", 1, 2, 3);
	rintf(ch, "%x+%o=%d", 0xabc, 100, 18);

	printf("%s\n", ch);

	return 0;
}

int main()
{
	//sscanf 从字符串中获取内容
	/*char ch[] = "abc+112=63";
	int a, b, c;
	sscanf(ch, "%x+%o=%d", &a, &b, &c);

	printf("%d\n", a);
	printf("%d\n", b);
	printf("%d\n", c);*/

	char ch[] = "hello world";
	char str1[100];
	char str2[100];

	//sscanf(ch, "%[^\n]", str1);
	sscanf(ch, "%5s%s", str1,str2);
	printf("%s\n", str1);
	printf("%s\n", str2);


	system("pause");
	return 0;
}