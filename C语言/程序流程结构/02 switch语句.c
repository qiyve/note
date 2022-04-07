#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	int score;
	scanf("%d", &score);
	switch (score/10)
	{
	case 10:
		printf("优秀\n");
		break;
	case 9:
		printf("优秀\n");
		break;
	case 8:
		printf("良好\n");
		break;
	case 7:
		printf("良好\n");
		break;
	case 6:
		printf("及格\n");
		break;
	case 5:
		printf("不及格\n");
		break;
	default:
		printf("不及格\n");
		break;
	}

	return 0;
}

