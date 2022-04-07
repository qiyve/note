#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	


int main()
{
	int score;
	scanf("%d", &score);

	//if(表达式){}
	//if(表达式){} else{}
	//if(表达式1){} else if(表达式2){} else{}
	//条件嵌套
	if (score > 700)
	{
		printf("考上清华");
		if (score > 720)
		{
			printf("我要学计算机\n");
		}
		else if (score > 710)
		{
			printf("我要学法");
		}
	}
	else if(score>650)
	{
		printf("考上北大");
	}

	else
	{
		printf("考上大专");
	}

	system("pause");
	return 0;
}