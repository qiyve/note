#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


//内存重置
int main01()
{
	//整形
	int* p = (int*)malloc(sizeof(int) * 10);

	//memset(void* s,int c,size_t n) 重置内存空间的值 
	//参数1：需要操作内存首地址 参数2：重置的值， 参数3：需要设置的大小（字节大小）
	memset(p, 0, sizeof(int)*10);  //一般内存空间重置为0是有效的 其他就不太准确
	//memset(p, 1, sizeof(int) * 10); err
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", p[i]);
	}

	//字符
	char ch[10];
	//memset(ch, 'A', sizeof(char) * 10); err
	memset(ch, 0, sizeof(char) * 10); 
	printf("%s\n", ch);

	return 0;
}

//内存拷贝
int main02()
{

	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
	int* p = (int*)malloc(sizeof(int) * 10);

	//字符串拷贝 strcpy()
	//内存拷贝 memcpy()

	memcpy(p, arr, sizeof(int) * 10);

	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", p[i]);
	}
	free(p); //释放内存


	char ch[] = "hello \0world";
	char str[100];
	//字符串拷贝遇到\0停止
	//strcpy(str, ch);

	//内存拷贝 拷贝内容和字节有管
	memcpy(str, ch, 13);
	printf("%s\n", str);
	for (int i = 0; i < 13; i++)
	{
		printf("%c", str[i]);
	}

	int arr0[] = { 1,2,3,4,5,6,7,8,9,10 };
	//如果拷贝的目标和源发生重叠 可能会报错
	memcpy(&arr[5], &arr[3], 20);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}

int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	//如果拷贝的目标和源发生重叠 可能会报错
	//memcpy(&arr[5], &arr[3], 20);

	//如果遇到重叠用memmove
	memmove(&arr[5], &arr[3], 20);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}

//内存比较
int main04()
{

	//int arr1[] = { 1,2,3,4,5,6,7,8,9 };
	//int arr2[] = { 1,2,3,4,5 };

	char arr1[] = "hello\0 world";
	char arr2[] = "hello\0 world";
	//strcmp();

	int value = memcmp(arr1, arr2, 13);

	printf("%d\n", value);

	return 0;
}

