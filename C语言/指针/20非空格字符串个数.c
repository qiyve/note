#include <stdio.h>

int getstrcount01(char* ch)
{
	int i = 0;
	int count = 0;
	while (ch[i])
	{
		if (ch[i] != ' ')
		{
			count++;
		}
		i++;
	}
	return count;
}

int getstrcount(char* ch)
{
	int count = 0;
	while (*ch)
	{
		if (*ch != ' ')count++;
		ch++;
	}
	return count;
}

int main01()
{
	char ch[] = " h e  ll o  wor l d";

	int len = getstrcount(ch);

	printf("%d\n", len);

	return 0;
}

int main()
{
	//统计字符串出现次数
	char ch[] = "hello world n ich oush ac ho un iz adi ";

	//存储字符串出现次数
	int arr[26] = { 0 };

	for (int i = 0; i < strlen(ch); i++)
	{
		//ch[i] ch中对应位置字符码值 - a对应的码值 得出对应码值的字符 每出现一次就++
		arr[ch[i] - 'a']++;
	}

	for (int i = 0; i < 26; i++)
	{
		if (arr[i]) //arr[i]!= 0
		{
			printf("字母：%c 出现次数%d\n", i + 'a', arr[i]);
		}
	}

	return 0;
}
