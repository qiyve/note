#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>

void my_strcpy(char* dest, const char* str)
{
	while (*dest++ = *str++);
}

void my_strncpy04(char* dest, char* str, size_t num)
{
	while ((*dest++ = *str++) && --num);
}

void my_strncpy01(char* dest, char* str, size_t n)
{
	for (int i = 0; i < n; i++)
	{
		dest[i] = str[i];
	}
}
void my_strncpy02(char* dest, char* str, size_t n)
{
	int i = 0;
	while (i < n)
	{
		*(dest + i) = *(str + i);
		i++;
	}
}
void my_strncpy(char* dest, char* str, size_t n)
{
	while (n--&&*str)
	{
		*dest = *str;

		dest++;
		str++;
	}
}

int main()
{
	char ch[] = "hello wrold";

	char str[100] = { 0 };

	//字符串拷贝
	//如果目标所指的内存空间不够大，可能会造成缓冲溢出的错误情况
	//strcpy(str, ch); //参数1 拷贝目标  参数2 源字符首地址
	//my_strcpy(str, ch);
	
	//字符串有限拷贝 
	//strncpy(str, ch, 6);
	my_strncpy(str, ch, 6);

	printf("%s\n", str);

	return 0;
}