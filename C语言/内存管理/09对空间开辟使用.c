#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>



int main01()
{
	//栈区大小  1M
	//int arr[820000/4] = { 0 };

	//开辟堆空间存储数据 malloc()
	int* p = (int*) malloc(sizeof(int));
	
	printf("%p\n", p);
	//使用堆空间
	*p = 123;
	printf("%d\n", *p);
	//释放堆区空间
	free(p);
	p = NULL;

	//p 野指针
	//printf("%p\n", p);
	//*p = 321;
	//printf("%d\n", *p);

	return 0;
}

int main()
{
	/*int* p = malloc(sizeof(int) * 8200000);

	printf("%p\n", p);
	free(p);*/

	int* p = (int*)malloc(sizeof(int) * 10); 
	for (int i = 0; i < 10; i++)
	{
		p[i] = i;
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", p[i]);
	}

	free(p);

	//if (!p)
	//{
	//	printf("程序异常\n");
	//	return -1;
	//}

	return 0;
}