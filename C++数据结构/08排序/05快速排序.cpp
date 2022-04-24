#include<iostream>
using namespace std;

//快速排序 升序
void QuickSort(int arr[], int stack, int end)
{
	int i = stack;
	int j = end;

	//基准数
	int temp = arr[stack];
	if (i < j)
	{
		while (i < j)
		{
			//从右向左 去找比基准数小的
			while (i < j && arr[j] >= temp)
			{
				j--;
			}
			//填坑
			if (i < j)
			{
				arr[i] = arr[j];
				i++;
			}

			//从左向右 找比基准数大的数
			while (i < j && arr[i] < temp)
			{
				i++;
			}
			//填空
			if (i < j)
			{
				arr[j] = arr[i];
				j--;
			}
		}

		//把基准数放到 j 和 i重叠的位置
		arr[i] = temp;
        //对左半部分进行快速排序
		QuickSort(arr, stack, i - 1);
		//对右半部分进行快速排序
		QuickSort(arr, i + 1, end);

	}
}

void PrintArray(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i]<<" ";
	}
	cout << endl;
}

int main()
{
	int arr[] = { 4,2,8,0,5,7,1,3,9 };
	int len = sizeof(arr) / sizeof(int);
	PrintArray(arr, len);
	QuickSort(arr, 0, len - 1);
	PrintArray(arr, len);



	system("pause");
	return 0;
}