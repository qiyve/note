#include <stdio.h>


int main01()
{
	/*char ch[] = "hello world";
	char* p = ch;*/
	//printf("%s\n", p);
	//printf("%c\n", *(p+1));
	
	char ch[] = "hello world"; //栈区字符串
	char* p = "hello wrold";   //数据区常量区字符串
	char*p1= "hello wrold";
	printf("%p\n", p);
	printf("%p\n", p1);

	//ch[2] = 'm';
	//p[2] = 'm'; err
	//*(p+1)='m'; err
	//printf("%c\n", ch[2]);
	//printf("%c\n", p[2]);

	system("pause");
	return 0;
}

int main()
{
	//字符串数组
	//指针数组 
	/*char ch1[] = { "hello" };
	char ch2[] = { "world" };
	char ch3[] = { "laowang" };
	char* arr[3] = { ch1,ch2,ch3 };*/
	
	//字符串数组
	char* arr[] = { "hello","wrold","laoli" };

	//for (int i = 0; i < 3; i++)
	//{
	//	printf("%s\n", arr[i]);
	//	//printf("%c\n", arr[i][0]); //首字母
	//}

	//字符串排序
	for (int i = 0; i < 3-1; i++)
	{
		for (int j = 0; j < 3-1-i; j++)
		{
			if (arr[j][0] > arr[j + 1][0])
			{
				char* temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		printf("%s\n", arr[i]);
	}
	system("pause");
	return 0;
}