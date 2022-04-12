#include <stdio.h>

char* my_strstr(char* src, char* dest)
{
	char* fsrc = src;//用于遍历循环的指针
	char* rsrc = src; //记录每次相同的首地址

	char* tdest = dest; //查找的字符串首地址

	while (*fsrc)
	{
		rsrc = fsrc;
		while (*fsrc == *tdest && *fsrc != '\0')
		{
			fsrc++;
			tdest++;
		}

		if (*tdest == '\0')
		{
			return rsrc;
		}
		//回滚
		fsrc = rsrc;
		tdest = dest;

		fsrc++;
	}
	return NULL;
}
int main()
{
	char src[] = "helloo world";
	char dest[] = "lloo";

	char* p = my_strstr(src,dest);

	printf("%s\n", p);
	
	system("pause");
	return 0;
}

