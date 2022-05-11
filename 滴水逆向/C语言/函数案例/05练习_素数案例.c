#include<stdio.h>

void  prime(int num)
{
	int i = 2;
	//循环次数
	//int j = num - 1;
	if (num >= i)
	{
		while (num)
		{
			if (num % i == 0)
			{
				printf("该数不是素数\n");
				
				break;
			}
			else
			{
				printf("该数为素数\n");
				break;
			}
			i++;
			//j--;
		}
	}
	else
	{
		printf("该数为素数\n");
	}
}

int main()
{
	prime(110);

	
	return 0;
}
