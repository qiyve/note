#include <stdio.h>

int main01()
{
	//定义数组 数组类型 数组名[元素个数] = {值1，值2....};
	//定义指针数组 
	int a = 10;
	int b = 20;
	int c = 30;

	int* arr[3] = { &a,&b,&c };
	//printf("%d\n", *arr[0]);
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", *arr[i]);
	}

	printf("指针数组大小：%d\n", sizeof(arr));
	printf("指针元素大小：%d\n", sizeof(arr[0]));


	system("pause");
	return 0;
}

int main()
{
	//指针数组里面元素存储的是指针
	int a[] = { 1,2,3 };
	int b[] = { 4,5,6 };
	int c[] = { 7,8,9 };
	//指针数组是一个特殊的二维数组的模型
	int* arr[] = { a,b,c };
	//printf("%p\n", arr);
	//printf("%p\n", &arr[0]);

	//printf("%d\n", arr[1][1]);
	
	//printf("%p\n", arr[0]);
	//printf("%p\n", a);
	//printf("%p\n", &a[0]);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//二维数组
			//printf("%d ", arr[i][j]);
			//printf("%d ", *(arr[i] + j)); //j表示偏移量
			printf("%d ", *(*(arr + i) + j));

		}
		printf("\n");
	}

	return 0;
	
}