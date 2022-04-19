#ifndef CIRCLELINKLIST
#define CIRCLELINKLIST

//编写针对链表结构体操作的API函数
#define CIRCLELINKLIST_TRUE 1
#define CIRCLELINKLIST_FALST 0

#include<stdio.h>
#include<stdlib.h>

//链表小结点
typedef struct CIRCLELINKNODE 
{
	struct CIRCLELINKNODE* next;
}CircleLinkNode;

//链表结构体
typedef struct CIRCLELINKLIST {

	CircleLinkNode head;
	int size;

}CircleLinkList;;

//比较回调
typedef int(*COMPARENODE)(CircleLinkNode*, CircleLinkNode*);
//打印回调
typedef void (*PRINTNODE)(CircleLinkNode*);

//编写针对链表结构体操作的API函数
#define CIRCLELINKLIST_TRUE 1
#define CIRCLELINKLIST_FALST 0

//初始化函数
CircleLinkList* Init_CircleLinkList();
//插入函数
void insert_CircleLinkList(CircleLinkList* clist, int pos, CircleLinkNode* data);
//获得第一个元素
CircleLinkNode* Frond_CircleLinkList(CircleLinkList* clist);
//根据位置删除
void RemovePos_CircleLinkList(CircleLinkList* clist,int pos);
//根据值删除
void RemoveByValue_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare);
//获得链表长度
int Size_CircleLinkList(CircleLinkList* clist);
//判断是否为空
int IsEmpty_CiecleLinkList(CircleLinkList* clist);
//查找
int Find_CircleLinkList(CircleLinkList* clist, CircleLinkNode* data, COMPARENODE compare);
//打印结点
void Print_CircleLinkList(CircleLinkList* clist, PRINTNODE print);
//释放内存呢
void FreeSpace_CircleLinkList(CircleLinkList* clist);



#endif 