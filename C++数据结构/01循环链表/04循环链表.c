#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"04CircleLinkList.h"

typedef struct PERSON 
{
	CircleLinkNode node;
	char nane[64];
	int age;
	int score;

}Person;

void MyPrint(CircleLinkNode* data)
{
	Person* p = (Person*)data;
	printf("Name：%s Age：%d score: %d\n", p->nane, p->age, p->score);
}

int MyCompare(CircleLinkNode* data1, CircleLinkNode* data2)
{
	Person* p1 = (Person*)data1;
	Person* p2 = (Person*)data2;

	if (strcmp(p1->nane, p2->nane) == 0 && p1->age == p2->age && p1->score == p2->score)
	{
		return CIRCLELINKLIST_TRUE;
	}
	return CIRCLELINKLIST_FALST;
}

int main()
{
	//创建循环列表
	CircleLinkList* clist = Init_CircleLinkList();

	//创建数据
	Person p1, p2, p3, p4, p5;
	strcpy(p1.nane, "aaa");
	strcpy(p2.nane, "bbb");
	strcpy(p3.nane, "ccc");
	strcpy(p4.nane, "ddd");
	strcpy(p5.nane, "eee");

	p1.age = 10;
	p2.age = 20;
	p3.age = 30;
	p4.age = 40;
	p5.age = 50;

	p1.score = 50;
	p2.score = 50;
	p3.score = 65;
	p4.score = 60;
	p5.score = 70;

	//数据入链表
	insert_CircleLinkList(clist, 0, (CircleLinkNode*)&p1);
	insert_CircleLinkList(clist, 0, (CircleLinkNode*)&p2);
	insert_CircleLinkList(clist, 0, (CircleLinkNode*)&p3);
	insert_CircleLinkList(clist, 0, (CircleLinkNode*)&p4);
	insert_CircleLinkList(clist, 0, (CircleLinkNode*)&p5);

	//打印
	Print_CircleLinkList(clist, MyPrint);

	//位置删除 3
	//RemovePos_CircleLinkList(clist, 3);
	//printf("--------------\n");
	//Print_CircleLinkList(clist, MyPrint);

	//值删除
	Person pDel;
	strcpy(pDel.nane, "aaa");
	pDel.age = 10;
	pDel.score = 50;
	RemoveByValue_CircleLinkList(clist,(CircleLinkNode*) &pDel, MyCompare);
	Print_CircleLinkList(clist, MyPrint);

	//大小
	int ret = Size_CircleLinkList(clist);
	printf("链表大小：%d\n", ret);

	//释放内存
	FreeSpace_CircleLinkList(clist);

	return 0;
}