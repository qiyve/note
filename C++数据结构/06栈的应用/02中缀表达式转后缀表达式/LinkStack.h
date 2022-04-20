#ifndef LINKSTACK_H
#define LINKSTACK_H
#include<stdio.h>
#include<stdio.h>

//链式栈的结点
typedef struct LINKNODE {
	struct LINKNODE* next;//Ctrl + R + R

}LinkNode;

//链式栈
typedef struct LINKSTACK {

	LinkNode head;
	int size;

}LinkStack;

//初始化函数
LinkStack* Init_LinkStack();
//入栈
void Push_LinkStack(LinkStack* stack, LinkNode* data);
//出栈
void Pop_LinkStack(LinkStack* stack);
//返回栈顶元素
LinkNode* Top_LinkStack(LinkStack* stack);
//返回元素个数
int Size_LinkStack(LinkStack* stack);
//清空栈
void Clera_LinkStack(LinkStack* stack);
//销毁栈
void FreeSpace_LinkStack(LinkStack* stack);


#endif 