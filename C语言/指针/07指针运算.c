#include <stdio.h>

void my_strcpy01(char* dest, char* ch)
{
	int i = 0;
	//while (ch[i] != '\0');
	//while (ch[i] != 0);
	while (ch[i])
	{

		dest[i] = ch[i];
		i++;
	}
	dest[i] = 0;// \0
}

void my_strcpy02(char* dest, char* ch)
{
	int i = 0;
	while (*(ch+i))
	{
		*(dest + i) = *(ch + i);
		i++;
	}
	*(dest + i) = 0; // \0
}

void my_strcpy03(char* dest, char* ch)
{
	while (*ch)
	{
		*dest = *ch;
		dest++;//指针+1 相当于指向数组的下一个元素 内存地址变化了sizeof（char）
		ch++;
	}
	*dest = 0;
}

void my_strcpy(char* dest, char* ch)
{
	while (*dest++ = *ch++);
	// *dest  *ch 
	// *dest = *ch 
	//  dest++ ch++
	
}

int main01()
{
	//字符串拷贝
	char ch[] = "hello world";
	char dest[100];
	
	my_strcpy(dest, ch);
	printf("%s\n", dest);

	system("pause");
	return 0;
}

int main02()
{

	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	//char* p ;
	int* p ;

	//arr/[-1] 数组下标越界

	p = &arr[3];
	printf("%p\n", p);
	//p--;//指针的减法运算和指针的类型有关
	//p--;
	//p--;

	//内存地址相差12 / sieof(int) =偏移量
	//int step = p - arr;

	//printf("%d\n", step);

	//指针操作数组时语序下标是负数
	printf("%d\n", p[-2]); //*(p-2)

	//printf("%p\n", p);
	//printf("%p\n", arr);


	system("pause");
	return 0;
}

int main()
{
	//指针和运算符操作
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int* p = arr;
	p = &arr[3];

	//野指针
	//p = p + arr; 错
	//p = p * arr;
	//p = p * 4;
	//p = p / arr;
	//p = p % 4;

	if (p > arr)
	{
		printf("真\n");
	}


	system("pause");
	return 0;
}