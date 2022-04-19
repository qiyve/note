#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"02LinKist.h"

//自定义数据类型
typedef struct PERSON
{
	char name[64];
	int age;
	int score;
}Preson;

//打印函数
void MyPrint(void* data)
{
	Preson* p = (Preson*)data;
	printf("Name:%s Age:%d Scoer:%d\n", p->name, p->age, p->score);
}

int main()
{
	//创建链表
	LinkList* list = Init_LinkList();

	//创建数据
	Preson p1 = { "aaa",16,100 };
	Preson p2 = { "bbb",17,70 };
	Preson p3 = { "ccc",12,82 };
	Preson p4 = { "ddd",19,65 };
	Preson p5 = { "fff",13,60 };

   //数据插入链表
	Insert_LinkList(list, 0, &p1);
	Insert_LinkList(list, 0, &p2);
	Insert_LinkList(list, 0, &p3);
	Insert_LinkList(list, 0, &p4);
	Insert_LinkList(list, 0, &p5);

	//打印
	Preint_LinkList(list, MyPrint);

	//删除 3
	RemoveByPos_LinkList(list, 3);
	//打印
	printf("--------------\n");
	Preint_LinkList(list, MyPrint);

	//返回第一个结点
	Preson*ret = (Preson*)Front_LinkList(list);
	printf("------第一个结点值为--------\n");
	printf("Name:%s Age:%d Scoer:%d\n", ret->name, ret->age, ret->score);

	//查找
	int fd = Find_LinkList(list, &p2);
	printf("------查找成功--------\n");
	printf("%d\n", fd);

	//销毁链表
	FreeSpace_LinkList(list);


	return 0;
}