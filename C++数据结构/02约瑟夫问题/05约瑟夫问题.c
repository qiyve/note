#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"04CircleLinkList.h"

#define M 8
#define N 3

typedef struct MYNUM {
	CircleLinkNode node;
	int val;

}MyNum;

void MyPrint(CircleLinkNode* data)
{
	MyNum* num = (MyNum*)data;
	printf("%d ", num->val);
	
}
int MyCompre(CircleLinkNode* data1, CircleLinkNode* data2)
{
	MyNum* num1 = (MyNum*)data1;
	MyNum* num2 = (MyNum*)data2;

	if (num1->val == num2->val)
	{
		return CIRCLELINKLIST_TRUE;
	}

	return CIRCLELINKLIST_FALST;
}


int main()
{
	//创建循环链表
	CircleLinkList* clist = Init_CircleLinkList();

	//链表插入数据
	MyNum num[M];
	for (int i = 0; i < M; i++)
	{
		num[i].val = i + 1;
		insert_CircleLinkList(clist, i, (CircleLinkNode*)&num[i]);
	}

	//打印
	Print_CircleLinkList(clist, MyPrint);
	printf("\n");

	//辅助指针
	int index = 1;
	CircleLinkNode* pCurrent = clist->head.next;
	while (Size_CircleLinkList(clist) > 1)
	{
		if (index == N)
		{
			MyNum* temNum = (MyNum*)pCurrent;
			printf("%d ", temNum->val);

			//缓存待删除的下一个结点
			CircleLinkNode* pNext = pCurrent->next;
			//根据值删除
			RemoveByValue_CircleLinkList(clist, pCurrent, MyCompre);
			pCurrent = pNext;
			if (pCurrent == &(clist->head))
			{
				pCurrent = pCurrent->next;
			}
			index = 1;
		}
		pCurrent = pCurrent->next;
		if (pCurrent == &(clist->head))
		{
			pCurrent = pCurrent->next;
		}

		index++;
	}

	if (Size_CircleLinkList(clist) == 1)
	{
		MyNum* temNum = (MyNum*)Frond_CircleLinkList(clist);
		printf("%d", temNum->val);
	}
	else
	{
		printf("出错\n");
	}


	
	return 0;
}