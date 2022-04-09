#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

int my_strcmp(char ch1[], char ch2[])
{
	int i = 0;
	while (ch1[i]==ch2[i])
	{
	  //是否到字符串结尾
		if (ch1[i] == '\0')
		{
			return 0;
		}
		i++;
	}
	return ch1 > ch2 ? 1 : -1;
}

int main()
{
	//比较两个字符串 如果相同返回0 如果不同返回 1或 -1
	char ch1[] = "hello";
	char ch2[] = "hello";

	int value = my_strcmp(ch1, ch2);
	printf("%d\n", value);

	system("pause");
	return 0;
}