#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAX 10

void BubbleSort(int* src,int len )
{
	for (int i = 0; i < len - 1; i++)
	{
		for (size_t j = 0; j < len - 1 - i; j++)
		{
			if (src[j] > src[j + 1])
			{
				int temp = src[j];
				src[j] = src[j + 1];
				src[j + 1] = temp;
		    }
		}
	}
}

int main()
{
	srand((size_t)time(NULL));
	int* p = (int*)malloc(sizeof(int) * MAX);

	printf("%p\n", p);

	for (int i = 0; i < MAX; i++)
	{
		p[i] = rand() % 100;
		printf("%d ", p[i]);
	}
	printf("\n");

	BubbleSort(p, MAX);

	for (int i = 0; i < MAX; i++)
	{
		//printf("%d ", p[i]);
		printf("%d ", *p);
		p++;
	}
	printf("\n");


	printf("%p\n", p);
	p -= MAX;
	printf("%p\n", p);

	free(p);

	system("pause");
	return 0;
}