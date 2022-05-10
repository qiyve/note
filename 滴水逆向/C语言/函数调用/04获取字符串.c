#include<stdio.h>

void  get_char(int a)
{
	char* c = "chinaÖĞ¹úverygoodÌì³¯nice";

	int i = 0;
	while (a)
	{
		printf("%c", c[i]);

		i++;
		a--;
	}
	printf("\n");
}

int main01()
{
	get_char(10);

	getchar();
	return 0;
}

int main()
{
	char c = 'a';
	char* p = c;

	printf("%p\n", &c);
	printf("%p\n", p);
	printf("%p\n", &p);

	return 0;
}