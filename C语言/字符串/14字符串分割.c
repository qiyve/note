#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>



int main01()
{
	//字符串截取 strtok 会破环源字符串  用\0替换分割的标志位
	char ch[] = "www.itcast.cn"; 
	// www \0 itcast.cn
	// www\0itcast\0cn
	char* p = strtok(ch, ".");

	printf("%s\n", p);

	p = strtok(NULL, ".");
	printf("%s\n", p);

	p = strtok(NULL, ".");
	printf("%s\n", p);
	/*printf("%s\n", ch);

	printf("%p\n", p);
	printf("%p\n", &ch);*/

	return 0;
}

int main02()
{
	char ch[] = "123456@qq.com";
	char str[100] = { 0 };

	//字符串备份
	strcpy(str, ch);
	//printf("%s\n", str);

	char* p = strtok(ch, "@");
	printf("%s\n", p);

	p = strtok(NULL, ".");
	printf("%s\n", p);

	return 0;
}
int main()
{
	//char ch[] = "nichousha\nchounizadi\nzaichouyigeshishi\nshishijiushishi\nguapi";
	char ch[] = "你瞅啥\n再瞅一个试试\n试试就试试瓜皮\n";


	char* p = strtok(ch, "\n");
	//printf("%s\n", p);

	while (p)
	{
		printf("%s\n", p);
		p = strtok(NULL, "\n");
	}

	return 0;
}