#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

void func01()
{
	printf("hello world\n");
}
//无参函数
int func02()
{
	return rand() % 10; 
}

int main01()
{
	srand((unsigned)time(NULL));

	func01();

	system("pause");
	return 0;
}

// 冒泡排序函数版  有参函数
void BubieSort(int arr[],int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

}

int main()
{
	int arr[] = { 5,3,7,8,4,2,1,10,6,9 };
	int len = sizeof(arr) / sizeof(arr[0]);

	BubieSort(arr, len);
	for (int i = 0; i < len; i++)
	{
		printf("%d\n", arr[i]);
	}

	system("pause");
	return 0;
}