#include<stdio.h>

void  prime(int num)
{
	int i = 2;
	//ѭ������
	//int j = num - 1;
	if (num >= i)
	{
		while (num)
		{
			if (num % i == 0)
			{
				printf("������������\n");
				
				break;
			}
			else
			{
				printf("����Ϊ����\n");
				break;
			}
			i++;
			//j--;
		}
	}
	else
	{
		printf("����Ϊ����\n");
	}
}

int main()
{
	prime(110);

	
	return 0;
}
