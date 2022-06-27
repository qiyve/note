#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//交换
template<class T>
void Swap(T& x,T &y)
{
	T temp;
	temp = x;
	x = y;
	y = temp;
}

//冒泡
template<class T>
void Sort(T arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(arr[j], arr[j + 1]);
			}
		}
	}
}

//折半查找
template<class T, class Y>
int MyFind(T arr, int len, Y Index)
{
	int begin = 0;  //起始下标
	int end = len - 1; //结束下标
	int num = 0;    // 用于判断

	while (begin <= end)
	{
		num = (begin + end) / 2; //( begin + end) >> 1
		if (arr[num] < Index)
		{
			begin = num + 1; // 在数组 右半部分
		}
		else if (arr[num] > Index)
		{
			end = num - 1; // 左半部分
		}
		else
		{
			return num; // 找到 返回该值 下标
		}

	}

	return -1; 
}

//测试
void test()
{
	int arr[] = { 2,7,9,6,7,1,3,5 };

	for (int i = 0; i < 8; i++)
	{
		printf("%d ", arr[i]);
	}printf("\n");

	Sort(arr, 8);
	//for (int i = 0; i < 8; i++)
	//{
	//	printf("%d ", arr[i]);
	//}printf("\n");

	int x = MyFind(arr, 8, 9);
	printf("%d\n", x);
}

int main01()
{
	test();

	return 0;
}


class Person
{
public:

	int x;
	Person()
	{		x = 100;	}
};

void Test()
{
	Person p1, p2, p3, p4, p5;
	Person arr[] = { p1,p2,p3,p4,p5 };

	// Sort(arr, 5); err 
	//2、冒泡排序：对结构体或者类进行排序，如果不能实现，找出问题所在.
	/* 
      错误 C2676	二进制“>”:“Person”不定义该运算符或到预定义运算符可接收的类型的转换	

	   原因：编译其不知道改如何比较结构体即成员， 解决办法：重载 < 或 > 运算符
	*/
}

int main()
{


	return 0;
}