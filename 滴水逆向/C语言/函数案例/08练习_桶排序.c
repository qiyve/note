#include<stdio.h>

//桶排序 int类型数组 桶的个数 排序数组中 最大值 + 1
//2 4 6 5 3 1 2 7

//0 1 2 1 1 1 1 1  桶初始化为 0 
//0 1 2 3 4 5 6 7  桶下标   代表分数   出现对应分数  在桶上记录 + 1 

//1 2 2 3 4 5 6 7

void func()
{
	
	int arr[] = { 2,4,6,5,3,1,2,7 };
	//创建桶  
	int arr2[8] = { 0 };

	for (int i = 0; i < 8; i++)
	{
		arr2[arr[i]]++; //统计
	}

	for (int i = 0; i < 8; i++) 
	{
		//读取并打印  j表示最少出现一次 否则不打印；
		//arr2[i] 存储出现次数， i 表示分数
		for (int j = 1; j <= arr2[i]; j++)  
		{
			printf("%d ", i); 
		}
	}
	printf("\n");
}


int main()
{
	func();

	system("pause");
	return 0;
}