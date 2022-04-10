#include <stdio.h>


int main01()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	//数组名是一个常量 不允许赋值
	// 数组名是数组首元素地址
	//arr = 100; //错
	int* p;
	p = arr;
	//printf("%p\n", p);
	//printf("%p\n", arr);

	*p = 123;
	//printf("%d\n", *p);
	//p++;

	//printf("%p\n", arr);
	//printf("%p\n", p);

	for (int i = 0; i < 10; i++)
	{
		//
		//printf("%d\n", *(arr + 1));//arr[1]
		//printf("%d\n", p[i]);
		//printf("%d\n", *(p + 1));
		printf("%d\n", *p++ );

	}

	//printf("%p\n", arr);
	//printf("%p\n", p);

	//两个指针相减 等到的结果是两个指针的偏移量(步长)
	//所有的指针类型 详见结果都是int 类型
	int step = p - arr; //3c +1= 40   相当于 sizeof(int)  40/sizeof(int)

	printf("%d\n", step);

	system("pause");
	return 0;
}

int main02()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	//指向数组的指针
	int* p = arr;

	//p是变量 arr是常量
	//p是一个针织 4个字节大小 
	//arr是一个数组 40个字节大小
	printf("指针类型大小：%d\n", sizeof(p));
	printf("数组大小：%d\n", sizeof(arr));


	//p[i];
	//*(p + i); i偏移量

	system("pause");
	return 0;
}


//数组作为函数参数会退化为指针 丢失数组的精度
void BubbleSort(int *arr,int len)
{
	int len = sizeof(arr) / sizeof(arr[0]);

	//printf("%d\n", sizeof(arr));

	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 -i; j++)
		{
		/*	if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}*/
			if (*(arr + j) > *(arr + j + 1))
			{
				int temp = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j + 1) = temp;
			}
		}
	}
}

int main()
{

	int arr[] = { 2,5,6,7,4,1,2,9,3,10 };

	BubbleSort(arr,10);
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", arr[i]);
	}

	system("pause");
	return 0;
}