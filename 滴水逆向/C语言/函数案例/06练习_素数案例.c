#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int prime(int num)
{

	int i = 2;
	int  r;

	if (num >= i)
	{
		while (num)
		{
			if (num % i == 0)
			{
				r = 0; //不是
				break;
			}
			else
			{
				r = 1; //是
				break;
			}
			i++;
			
		}
	}
	else
	{
		r = 1; //为1时
	}
	return r;
}

int main()
{
	//获取
	int n;
	scanf("%d", &n);

	if (prime(n))
	{
		printf("该数为素数\n");
	}
	else
	{
		printf("该数不是素数\n");
	}

	
	return 0;
}
