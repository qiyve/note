#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>

void my_strcat(char* dest, char* src)
{
	while (*dest)dest++; //获取dest字符串中\0的位置
	while (*dest++ = *src++);
}

void my_strncat(char* dest, char* src, size_t n)
{
	while (*dest)dest++;
	while ((*dest++ = *src++) && --n);
}

int main()
{
	char dest[100] = "hello";
	char src[] = "wrold";

	//字符串追加
	//strcat(dest, src);
	//my_strcat(dest, src);

	//有限追加
	//strncat(dest, src, 3);
	my_strncat(dest, src, 3);
	printf("%s\n", dest);

	system("pause");
	return 0;
}