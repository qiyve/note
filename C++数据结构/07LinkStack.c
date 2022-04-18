#include"07LinkStack.h"


//初始化函数
LinkStack* Init_LinkStack()
{
	LinkStack* stack = (LinkStack*)malloc(sizeof(LinkStack));
	stack->size = 0;
	stack->head.dext = NULL;
	return stack;
}
//入栈
void Push_LinkStack(LinkStack* stack, LinkNode* data)
{
	if (stack == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	//入栈
	data->dext = stack->head.dext;
	stack->head.dext = data;
	stack->size++;

}
//出栈
void Pop_LinkStack(LinkStack* stack)
{
	if (stack == NULL)
	{
		return ;
	}
	if (stack->size == 0)
	{
		return;
	}
	
	//第一个有效结点
	LinkNode* pNext = stack->head.dext;
	stack->head.dext = pNext->dext;

	stack->size--;
}
//返回栈顶元素
LinkNode* Top_LinkStack(LinkStack* stack)
{
	if (stack == NULL)
	{
		return -1;
	}
	if (stack->size == 0)
	{
		return -1;
	}
	return stack->head.dext;
}
//返回元素个数
int Size_LinkStack(LinkStack* stack)
{
	if (stack == NULL)
	{
		return -1;
	}

	return stack->size;
}
//清空栈
void Clera_LinkStack(LinkStack* stack)
{
	if (stack == NULL)
	{
		return;
	}
	stack->head.dext = NULL;
	stack->size = 0;
}
//销毁栈
void FreeSpace_LinkStack(LinkStack* stack)
{
	if (stack == NULL)
	{
		return;
	}
	free(stack);

}
