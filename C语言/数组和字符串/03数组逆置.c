#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main()
{
	//数组逆置
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int i = 0;
	int j = sizeof(arr) / sizeof(arr[0]) - 1;//j的元素个数

	while (i<j)
	{
		//通过临时变量交换数据
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;

		i++;
		j++;
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", arr[i]);
	}
	

	system("pause");
	return 0;

}

int main01()
{
	//数组逆置
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int j = sizeof(arr) / sizeof(arr[0])-1;

	for (int i = 0; i < 10; i++)
	{
		if (i < j)//相等就结束
		{
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}

		j--; 
	}

	for (int i = 0; i < 10; i++)
	{
		printf(" %d", arr[i]);
	}

	system("pause");
	return 0;
}