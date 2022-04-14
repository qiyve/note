#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//内存常见问题
int main01()
{
	//数组下标越界
	char ch[11] = "hello world";

	char* p = (char*)malloc(sizeof(char) * 11);
	strcpy(p, "hello world");
	printf("%s\n", p);
	free(p); // err 释放过多内存 

	return 0;
}

int main02()
{
	//野指针
	//int* p = (int*)malloc(0);
	//开辟空间和类型对应 而且不能超过界线
	int* p = (int*)malloc(10);
	// int* p = (int*)malloc(sizeof(int)*10); ok
	p[0] = 123;
	p[1] = 456;
	p[2] = 789;

	printf("%p\n", p);
	//*p = 100;
	printf("%d\n", *p);
	printf("%d\n", *(p+1));
	free(p);

	return 0;
}

int main03()
{
	int* p = (int*)malloc(sizeof(int) * 10);


	for (int i = 0; i < 10; i++)
	{
		//指针叠加 不断改变指针方向 释放会出错
		*p++ = i; // *p = i;  p++;
	}

	free(p);
	//堆区空间不允许多次释放
	p = NULL; 
	//空指针允许多次释放
	free(p);
	free(p);
	free(p);
	free(p);

	return 0;
}

void func01(int* p)
{
	p = (int*)malloc(sizeof(int) * 10);
	printf("形参：%p\n", p);
}

void func02(int** p)
{
	*p = (int*)malloc(sizeof(int) * 10);
	printf("形参：%p\n", *p);
}

//返回值
int* func03()
{
	int* p = (int*)malloc(sizeof(int) * 10);
	return p;
}

int main()
{
	int* p = NULL;
	//值传递
	//func01(p); err
	//地址传递
    // func02(&p); ok
	p = func03();
	printf("实参：%p\n", p);

	for (int i = 0; i < 10; i++)
		p[i] = i;

	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", p[i]);
	}

	free(p);

	return 0;
}