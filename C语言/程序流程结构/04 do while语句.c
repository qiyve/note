#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>


int main01()
{
	
	int i = 0;

	do 
	{
		printf("%d\n", i);
		i++;
	} while (i < 10);
	

	//while (i)
	//{
	//	printf("%d\n", i);
	//	i++;
	//}
}
int main()
{
	//水仙花  从100到999 各个位数立方和 相加等与这个数本身称为水仙花数

	int i = 100;
	do
	{
		//个位
		int a = i % 10;
		//十位
		int b = i / 10 % 10;
		//百位
		int c = i / 100;

		if (a * a * a + b * b * b + c * c * c == i)
		{
			printf("%d\n", i);
		}
		i++;

	} while (i <= 999);

	return 0;
}