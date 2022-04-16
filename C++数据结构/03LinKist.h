#ifndef LINKLIST_h
#define LINKLIST_h

#include<stdio.h>
#include<stdlib.h>

//链表小结点
typedef struct LINKNODE
{
	struct LINKNODE* next;
}LinkNode;

//链表结点
typedef struct LINKLIST 
{
	LinkNode head;
	int size;
}LinkList;

//打印回调函数
typedef void(*PRINTNODE)(LinkList* data);

//初始化链表
LinkList* Init_LinkList();
//插入
void Insert_LinkList(LinkList* list, int pos, LinkNode* data);
//删除
void Remove_LinkList(LinkList* list, int pos);
//查找
int Find_LinkList(LinkList* list, LinkList* data);
//返回链表大小
int Size_LinkList(LinkList* list);
//打印
void Print_LinkList(LinkList* list, PRINTNODE print);
//释放链表内存
void FreeSpace_LinkList(LinkList* list);

#endif 