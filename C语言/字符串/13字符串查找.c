#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>

char* my_strchr(const char* s, char c)
{
	while (*s)
	{
		if (*s == c)
			return s; 
		s++;
	}
	return NULL;
}

char* my_strstr( char* src, char* dest )
{
	char* fsrc = src;
	char* rsrc = src;
	char* tdest = dest;

	while (*fsrc)
	{
		rsrc = fsrc;
		while (*fsrc == *tdest && *fsrc)
		{
			fsrc++;
			tdest++;
		}
		
		if (*tdest == '\0')
		{
			return rsrc;
		}
		//»Ø¹ö
		fsrc = rsrc;
		tdest = dest;
		
		fsrc++;
	}
	return NULL;
}

int main01()
{
	//strstr(const char* haystack, const char* needle)
	//ÔÚ×Ö·û´®haystackÖĞ²éÕÒ×Ö·û´®needle³öÏÖµÄÎ»ÖÃ
	char ch[] = "hello world";
	char c = 'l';

	//char* p = strchr(ch, c);
	char* p = my_strchr(ch, c);
	printf("%s\n", p);


	system("pause");
	return 0;
}

int main()
{
	//×Ö·û´®²éÕÒ×Ö·û´®
	char ch[] = "hello world";
	char str[] = "llo";

	//char* p = strstr(ch, str);
	char* p = my_strstr(ch,str);

	printf("%s\n", p);


	return 0;
}