#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

//动态增长内存，策略 将存放的内存放到那？堆上
//动态数组 如果5个元素 申请内存 拷贝数据 释放内存6 第七个插入？ 
//容量capacity便是我的这块内存空间一共可以存放多少元素
//size概念 记录当前数组中具体的元素个数


typedef struct DYNAMICARRAY
{
	int* pAddr;//存放数据地址
	int size; //当前大小
	int capacity; //容量，我容器当前最大能容纳多少元素

}Dynamic_Array;

//写一系列的相关对 DYNAMICARRAY结构体操作的函数

//初始化
Dynamic_Array* Init_Array();
//插入
void PushBack_Array(Dynamic_Array* arr, int value);
//根据位置删除
void RemoveByPos_Array(Dynamic_Array* arr, int pos);
//根据值删除
void RemoveByValue_Array(Dynamic_Array* arr, int value);
//查找
int Find_Array(Dynamic_Array* arr, int value);
//打印
void Print_Array(Dynamic_Array* arr);
//释放动态数组的内存
void FreeSpace_Array(Dynamic_Array* arr);

//清空数组
void Clear_Array(Dynamic_Array* arr);
//获取动态数组容量
int Capacity_Array(Dynamic_Array* arr);
//获取动态数组当前元素个数
int Size_Array(Dynamic_Array* arr);
//根据位置获取某个位置的元素
int At_Array(Dynamic_Array* arr, int pos);





#endif 
