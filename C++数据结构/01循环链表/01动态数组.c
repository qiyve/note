#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"DynamicArray.h"

void test01()
{
//初始化动态数组对象
	Dynamic_Array* myArray = Init_Array();
	//打印大小 	容量
	printf("数组大小%d\n", Size_Array(myArray));
	printf("数组容量：%d\n", Capacity_Array(myArray));
	//插入元素
	for (int i = 0; i < 20; i++)
	{
		PushBack_Array(myArray, i);
	}

	//删除
	/*RemoveByPos_Array(myArray, 5); 位置
	RemoveByValue_Array(myArray, 2); 值 */
	//打印
	Print_Array(myArray);

	//查找第10个位置
	int pos = Find_Array(myArray, 5);
	printf("10号位置查到：pos:%d %d\n", pos, At_Array(myArray, pos));

	//释放
	FreeSpace_Array(myArray);

}

int main()
{
	test01();

	return 0;
}