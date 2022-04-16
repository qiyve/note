#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"03LinKist.h"

typedef struct PERSON {

	LinkNode node; 

	char name[64];
	int age;
}Person;

//打印函数
void MyPrint(LinkNode* data)
{
	Person* p = (Person*)data;
	printf("Name:%s Age:%d\n", p->name, p->age);
}

int main()
{
	//创建链表
	LinkList* list = Init_LinkList();

	//创建数据
	Person p1, p2, p3, p4, p5;

	strcpy(p1.name, "aaa");
	strcpy(p2.name, "bbb");
	strcpy(p3.name, "ccc");
	strcpy(p4.name, "ddd");
	strcpy(p5.name, "eee");

	p1.age = 10;
	p2.age = 20;
	p3.age = 30;
	p4.age = 40;
	p5.age = 50;

	//将结点插入链表
	Insert_LinkList(list, 0, (LinkNode*)&p1);
	Insert_LinkList(list, 0, (LinkNode*)&p2);
	Insert_LinkList(list, 0, (LinkNode*)&p3);
	Insert_LinkList(list, 0, (LinkNode*)&p4);
	Insert_LinkList(list, 0, (LinkNode*)&p5);

	//打印
	Print_LinkList(list, MyPrint);

	//链表大小
	int ret = Size_LinkList(list);
	printf("链表大小：%d\n", ret);

	//释放
	FreeSpace_LinkList(list);



	return 0;
}