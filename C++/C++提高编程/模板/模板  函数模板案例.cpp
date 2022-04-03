#include<iostream>
using namespace std;

//实现通用 对数组进行排序函数
//规则 从小到大
//算法 选择排序
//测试 char 数组、int 数组

//交换函数模板
template<class T>
void mySwap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

//排序算法
template<class T>
void mySort(T arr[],int len)
{
	//选择排序
	for (int i = 0; i < len; i++)
	{
		int max = i;//认定最大值下标

		for (int j = i + 1; j < len; j++)
		{
			//认定的最大值 比 遍历出的数组 要小，说明 j 下标的元素才是真正的最大值 
			if (arr[max] < arr[j])
			{
				max = j;//更新最大值下标
			}
		}
		//如果认定的最大值 和 计算出的最大值不相等 交换它们
		if (max != i)
		{
			//交换max和i元素
			mySwap(arr[max],arr[i]);
		}
	}
}

//打印输出模板
template<class T>
void printArray(T arr[],int len)
{
	cout << "排序后的结果：";
	for (int i = 0; i < len; i++)
	{
		cout <<  arr[i] << " ";
	}
	cout << endl;
}

void test01()
{
	//测试 char 数组
	char charArr[] = "abcdef";
	//计算数组长度
	int len = sizeof(charArr) / sizeof(char);

	mySort(charArr, len);
	printArray(charArr, len);
}

void test02()
{
	//测试 int 数组
	int inArr[] = { 1,4,5,2,3,6 };

	int len = sizeof(inArr) / sizeof(int);

	mySort(inArr, len);
	printArray(inArr, len);
}
int main()
{
	//test01();

	test02();
	

	system("pause");
	return 0;
}