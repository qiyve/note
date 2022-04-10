#include <stdio.h>

//去空格
void remove_space01(char* ch)
{
	char str[100] = { 0 };
	char* temp = str;

	int i = 0;
	int j = 0;
	while (ch[i] != '\0')
	{
		if (ch[i] != ' ')
		{
			str[j] = ch[i];
			j++;
		}
		i++;
	}
	//printf("%s\n", str);

	while (*ch++ = *temp++);
}

void remove_space(char* ch)
{
	//用来遍历字符串
	char* ftemp = ch;
	//记录非空格字符串
	char* rtemp = ch;

	while (*ftemp)
	{
		if (*ftemp != ' ')
		{
			*rtemp = *ftemp;
			rtemp++;
		}
		ftemp++;
	}
	*rtemp = 0;
}

int main()
{

	char ch[] = "h e l l o w o rld";
	
	remove_space(ch);
	printf("%s\n", ch);


	system("pause");
	return 0;
}
