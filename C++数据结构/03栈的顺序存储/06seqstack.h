#ifndef SEQSTACK_H
#define SEQSTACK_H
#include<stdio.h>
#include<stdio.h>

//数组去模拟栈的顺序存储
#define MAX_SIZE 1024
#define SEQSTACK_TRUE 1
#define SEQSTACK_FLAST 0


typedef struct SEQSTACK {

	void* data[MAX_SIZE];
	int size;
}SeqStack;

//初始化栈
SeqStack* Init_SeqStack();
//入栈
void Push_SeqStack(SeqStack* stack, void* data);
//返回栈顶元素
void* Top_SeqStack(SeqStack* stack);
//出战
void Pop_SeqStack(SeqStack* stack);
//判断是否为空
int IsEmpty(SeqStack* stack);
//返回栈中的元素个数
int Size_SeqStack(SeqStack* stack);
//释放
void FreeSpace(SeqStack* stack);


#endif 