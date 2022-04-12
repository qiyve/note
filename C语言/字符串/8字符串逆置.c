#include <stdio.h>

void inverse01(char* ch)
{
	int i = 0;
	int j = strlen(ch) - 1; //下标
	while (i < j)
	{
		char temp = ch[i];
		ch[i] = ch[j];
		ch[j] = temp;
		
		i++;
		j--;
	}
}

void inverse(char* ch)
{
	char* ftemp = ch; 
	char* btemp = ch + strlen(ch) - 1; //起始下标加偏移量 -1
	
	while (ftemp < btemp)
	{
		char* temp = *ftemp;
		*ftemp = *btemp;
		*btemp = temp;

		ftemp++;
		btemp--;
	}
}


int main01()
{
	char ch[] = "hello wrold";

	inverse(ch);
	printf("%s\n", ch);

	return 0;
}

char symm(char* ch)
{
	char* ftemp = ch;
	char* btemp = ch + strlen(ch) - 1;

	while (ftemp < btemp)
	{
		if (*ftemp == *btemp)
			return 0;

		ftemp++;
		btemp--;
	}
	return 1;
}

int main()
{
	//回文字符串
	// abcba   abccba 

	char ch[] = "abccba";

	int value = symm(ch);

	if (!value)
	{
		printf("相同\n");
	}
	else
	{
		printf("不相同\n");
	}
}