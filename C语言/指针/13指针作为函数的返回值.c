#include <stdio.h>

char* my_strchar01(char* str, char ch)//ch´ú±í×Ö·û
{
	int i = 0;
	//str[i]!='\0'
	while (str[i])
	{
		if (str[i] == ch)
		{
			return &str[i];
		}
		i++;
	}

	return NULL;
}

char* my_strchar(char* str, char ch)
{
	while (*str)
	{
		if (*str == ch)
			return str;
		str++;
	}
	return NULL;
}

int main()
{
	char str[] = "hello world";
	char* p = my_strchar(str, 'o');

	if (p == NULL)
	{
		printf("Î´ÕÒµ½\n");
	}
	else
	{
		printf("%s\n", p);
	}

	system("pause");
	return 0;
}

