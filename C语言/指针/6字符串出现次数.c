#include <stdio.h>

char* my_strstr(char* str, char* dest)
{
	char* fstr = str;
	char* rstr = str;
	char* tdest = dest; //查找的字符串首地址

	while (*fstr)
	{
		rstr = fstr;
		while (*fstr == *tdest && *fstr != '\0')
		{
			fstr++;
			tdest++;
		}

		if (*tdest == '\0')
		{
			return rstr;
		}

		fstr = rstr;
		tdest = dest;

		fstr++;
	}

	return NULL;
}


int main01()
{
	char* str = "lloabclloasdllozzxllo";

	char ch[] = "llo";
	char* p = my_strstr(str, ch);
	int count = 0;//记录次数

	while (p)
	{
		count++;

		p += strlen(ch);
		p = my_strstr(p, ch);
	}

	printf("llo在字符串中出现：%d\n",count );

	return 0;
}

int main()
{
	char* str = "lloabclloasdllozzxllo";

	char ch[] = "llo";
	char* p = my_strstr(str, ch);
	int count = 0;//记录次数

	do
	{
		if (p)
		{
			count++;
			p += strlen(ch);
			p = my_strstr(p, ch);
		}
	} while (p);

	printf("llo在字符串中出现：%d\n", count);

	return 0;
}