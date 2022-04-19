#include"DynamicArray.h"


//动态数组初始化
Dynamic_Array* Init_Array()
{
	//申请内存 ???
	Dynamic_Array* myArray = (Dynamic_Array*)malloc(sizeof(Dynamic_Array));//这里bug sizeof(Dynamic_Array*)
	//初始化
	myArray->size = 0;
	myArray->capacity = 20;
	myArray->pAddr = (int*)malloc(sizeof(int) * myArray->capacity);

	return myArray;
}
//插入
void PushBack_Array(Dynamic_Array* arr, int value)
{
	if (arr == NULL)
	{
		return;
	}

	//判断空间是否足够
	if (arr->size == arr->capacity)
	{
		//第一步 申请一块更大的空间 新空间是旧空间的2倍
		int* newSpace = (int*)malloc(sizeof(int) * arr->capacity * 2);
		//第二部 拷贝数据到新空间
		memcpy(newSpace, arr->pAddr, arr->capacity * sizeof(int));
		//第三步 释放旧空间
		free(arr->pAddr);

		//更新容量
		arr->capacity = arr->capacity * 2;
		arr->pAddr = newSpace;
	}

	//插入新元素
	arr->pAddr[arr->size] = value;
	//更新元素个数
	arr->size++;
}

//根据位置删除
void RemoveByPos_Array(Dynamic_Array* arr, int pos)
{
	if (arr == NULL)
	{
		return;
	}
	//判断位置是否有效
	if (pos < 0 || pos >= arr->size)
	{
		return;
	}

	//删除元素
	for (int i = pos; i < arr->size - 1; i++)
	{
		arr->pAddr[i] = arr->pAddr[i + 1];
	}
	arr->size--;
}
//根据值删除value 第一次出现的位置
void RemoveByValue_Array(Dynamic_Array* arr, int value)
{
	if (arr == NULL)
	{
		return;
	}
	int pos = Find_Array(arr, value);
	//根据位置删除
	RemoveByPos_Array(arr, pos);
}
//查找
int Find_Array(Dynamic_Array* arr, int value)
{
	if (arr == NULL)
	{
		return -1;
	}
	//查找
	int pos = -1;
	for (int j = 0; j < arr->size; j++)
	{
		if (arr->pAddr[j] == value)
		{
			pos = j;
			break;
		}
	}

	return pos;
}
//打印
void Print_Array(Dynamic_Array* arr)
{
	if (arr == NULL)
	{
		return;
	}

	for (int i = 0; i < arr->size; i++)
	{
		printf("%d ", arr->pAddr[i]);
	}
	printf("\n");
}
//释放动态数组的内存
void FreeSpace_Array(Dynamic_Array* arr)
{
	if (arr == NULL)
	{
		return;
	}

	if (arr->pAddr != NULL)
	{
		free(arr->pAddr);
	}
	free(arr);
}
//清空数组
void Clear_Array(Dynamic_Array* arr)
{
	if (arr == NULL)
	{
		return;
	}
	//pAdrr-> 空间
	arr->size = 0;

}
//获取动态数组容量
int Capacity_Array(Dynamic_Array* arr)
{
	if (arr == NULL)
	{
		return -1;
	}
	return arr->capacity;
}
//获取动态数组当前元素个数
int Size_Array(Dynamic_Array* arr)
{
	if (arr == NULL)
	{
		return -1;
	}
	return arr->size;
}
//根据位置获取某个位置的元素
int At_Array(Dynamic_Array* arr, int pos)
{
	return arr->pAddr[pos];
}