#include <stdio.h>


int main01()
{
	int a[] = { 1,2,3 };
	int b[] = { 4,5,6 };
	int c[] = { 7,8,9 };
	//指针数组是一个特殊的二维数组的模型
	//指针数组对应二级指针
	int* arr[] = { a,b,c };

	//指针数组和二级指针建立关系
	int** p = arr;

	//printf("%d\n", **p); //arr[0][0]  a[0]
	//二级指针加偏移量 相当于跳过了一个一维数组大小
	//printf("%d\n", **(p + 1)); // arr[1][0]
	
	//一级指针加偏移量 相当于跳过了一个元素
	//printf("%d\n", *(*p + 1));  //arr[0][1]

	//printf("%d\n", *(*(p + 1) + 1)); //*(p+1) b的地址

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//printf("%d ", p[i][j]); //二维数组方式
			//printf("%d ", *(p[i] + j)); //指针数组 j偏移量
			printf("%d ", *(*(p + i) + j));//二级指针
		}
		//printf("\n");
		puts(""); //也可用做换行
	}

	system("pause");
	return 0;
}

int main()
{
	int a = 10;
	int b = 20;
	int* p = &a;
	int** pp = &p;

	//*pp = &b;// 等价于 p = &d
	**pp = 100;
	//*pp = 100; err

	printf("%d\n", *p);
	printf("%d\n", a);

	system("pause");
	return 0;
}