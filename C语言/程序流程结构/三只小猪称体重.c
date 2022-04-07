#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main()
{
	/*int num1;
	int num2;
	int num3;
	printf("请输入小猪A的体重:\n");
	scanf("%d", &num1);
	printf("请输入小猪B的体重:\n");
	scanf("%d", &num2);
	printf("请输入小猪C的体重:\n");
	scanf("%d", &num3);*/

	int A, B, C;
	printf("请输入三只小猪的体重:\n");
	scanf("%d%d%d", &A,&B,&C);

	if (A>B)
	{
		if (A > C)
		{
			//a>c
			printf("小猪A最重\n");
		}
		else
		{
			//c<a
			printf("小猪C最重\n");
		}
		
	}
	else  //a<b
	{
		if (B >C)
		{
			//b>c
			printf("小猪B最重\n");
		}
		else
		{
			//c>b
			printf("小猪C最重\n");
		}
	}



	system("pause");
	return 0;
}