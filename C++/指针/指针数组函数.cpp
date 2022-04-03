
#include <iostream>
using namespace std;
//2、创建函数 冒泡排序  参数1 数组的首地址； 参数2 数组的长度
void bubbleSort(int *arr, int len)
{
	//外层循环轮数 轮数 = 数组长度（len） -1
	for(int i=0;i<len;i++)
	{  
		//内层循环列数  列数 = 元素长度(len) - 轮数 -1 
		for (int j = 0; j < len - i - 1; j++)
		{
		//如果 j > j+1的值  交换数字
			if (arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j ]=arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}
//打印输出函数
void printArray(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << endl;
	}
}

int main()
{
	//1.创建数组
	int arr[9] = { 7,6,2,1,3,4,9,5,8 };

	//数组长度
	int len = sizeof(arr) / sizeof(arr[0]);
	
	//2、创建函数 实现冒泡排序
	bubbleSort(arr, len);

	//3、打印输出
	printArray(arr, len);


	system("pause");
	return 0;
}
