#include <stdio.h>

void my_strcat01(char* ch1, char* ch2)
{
	int i = 0;
	//strlen() 可以统计字符串的有效个数
	while (ch1[i] != '\0')
	{
		i++;
	}
	/*printf("%d\n", i);
	printf("%d\n", strlen(ch1));*/

	int j = 0;
	while (ch2[j] != '\0')
	{
		ch1[i + j] = ch2[j];
		j++;
	}

	ch1[i + j] = 0;
}

void my_strcat02(char* ch1, char* ch2)
{
	int i = 0;
	//while (*(ch1 + i) != '\0')
	//while (*(ch1 + i) != 0)
	while (*(ch1 + i) != '\0')
	{
		i++;
	}
	int j = 0;
	while (*(ch2+j)!='\0')
	{
		*(ch1 + i + j) = *(ch2 + j);
		j++;
	}
	*(ch1 + i + j) = 0;
}

void my_strcat03(char* ch1, char* ch2)
{
	while (*ch1)ch1++;
	/*while (*ch1++);执行到\0又进行了一次++
	ch1--;*/
	while (*ch2)
	{
		*ch1 = *ch2;
		ch1++;
		ch2++;
	}
	*ch1 = 0;

}

void my_strcat(char* ch1, char* ch2)
{
	while (*ch1)ch1++; // /0的位置
	while (*ch1++ = *ch2++); //  *ch1  *ch2 ->  ch1= ch2  -> ch1++  *ch2++ 
}

int main()
{

	char ch1[100] = "hello";
	char ch2[] = "world";

	my_strcat(ch1, ch2);

	printf("%s\n", ch1);

	system("pause");
	return 0;
}
