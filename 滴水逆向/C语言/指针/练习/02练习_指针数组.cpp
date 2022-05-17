#include<stdio.h>


void Function()
{
	int arr[5] = { 1,2,3,4,5 };
	int* p = arr;
	//完成代码，实现数组值的互换
	//..此处添加代码，使用指针，将数组的值倒置
	for (int k = 0; k < 5; k++)
	{
		printf("%d ", *(p + k));
	}
	printf("\n");
	
		
	int i = 0;
	int j = 5-1;
	while (j > i)
	{
		int temp = *(p + i);
		*(p + i) = *(p + j);
		*(p + j) = temp;

		i++;
		j--;
	}
	//打印数组值的代码已经写完，不需要修改				
	for (int k = 0; k < 5; k++)
	{
		printf("%d ", *(p + k));
	}

}

int main()
{
	Function();
 
	return 0;
}
