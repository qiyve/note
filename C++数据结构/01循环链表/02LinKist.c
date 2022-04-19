#include"02LinKist.h"


//初始化链表
LinkList* Init_LinkList()
{
	LinkList* list = (LinkList*)malloc(sizeof(LinkList));
	list->size = 0;

	//头节点 是不保存数据信息
	list->head = (LinkNode*)malloc(sizeof(LinkNode));
	list->head->data = NULL;
	list->head->next = NULL;

	return list;
}
//指定位置插入
void Insert_LinkList(LinkList* list, int pos, void* data)
{
	if (list == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	//友好处理,pos越界  默认插入尾部
	if (pos<0 || pos>list->size)
	{
		pos = list->size;
	}

	//创建新的结点
	LinkNode* newnode = (LinkNode*)malloc(sizeof(LinkNode));
	newnode->data = data;
	newnode->next = NULL;

	//找节点
	//辅助指针变量
	LinkNode* pCurrent = list->head;
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}

	//新节点如链表
	newnode->next = pCurrent->next;
	pCurrent->next = newnode;

	list->size++;
}
//删除指定位置的值
void RemoveByPos_LinkList(LinkList* list, int pos)
{
	if (list == NULL)
	{
		return;
	}
	if (pos<0 || pos>list->size)
	{
		return;
	}

	//查找前删除结点的前一个结点
	LinkNode* pCurrent = list->head;
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}

	//缓存删除的检点
	LinkNode* pDel = pCurrent->next;
	pCurrent->next = pDel->next;
	//删除节点内的内存
	free(pDel);

	list->size--;
}
//获得链表长度
int Size_LinkList(LinkList* list)
{
	return list->size;
}

//查找
int Find_LinkList(LinkList* list, void* data)
{
	if (list == NULL)
	{
		return -1;
	}
	if (data == NULL)
	{
		return-1;
	}

	//遍历查找
	LinkNode* pCurrent = list->head->next;
	int i = 0; //记录位置 
	while (pCurrent != NULL)
	{
		if (pCurrent->data == data)
		{
			break;
		}
		pCurrent = pCurrent->next;
		i++;
	}

	return i;
}

//返回第一个结点
void* Front_LinkList(LinkList* list)
{
	return list->head->next->data;
}

//打印链表结点
void Preint_LinkList(LinkList* list, PRINTLINKNODE print)
{
	if (list == NULL)
	{
		return;
	}

	//辅助指针变量
	LinkNode* pCurrent = list->head->next;
	while (pCurrent != NULL)
	{
		print(pCurrent->data);
		pCurrent = pCurrent->next; //偏移
	}

}

//释放链表的内存
void FreeSpace_LinkList(LinkList* list)
{
	if (list == NULL)
	{
		return;
	}

	//辅助指针变量
	LinkNode* pCurrent = list->head;
	while (pCurrent != NULL)
	{
		//缓存下一个结点
		LinkNode* pNext = pCurrent->next;
		free(pCurrent);
		pCurrent = pNext;
	}
	//释放列表内存
	free(list);
	list->size = 0;
}
