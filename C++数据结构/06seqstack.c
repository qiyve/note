#include"06seqstack.h"


//初始化栈
SeqStack* Init_SeqStack()
{
	SeqStack* stack = (SeqStack*)malloc(sizeof(SeqStack));
	for (int i = 0; i < MAX_SIZE; i++)
	{
		stack->data[i] = NULL;
	}
	stack->size = 0;
	return stack;
}
//入栈
void Push_SeqStack(SeqStack* stack, void* data)
{
	if (stack->size == MAX_SIZE)
	{
		return;
	}

	if (stack == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	//入栈
	stack->data[stack->size] = data;
	stack->size++;

}
//返回栈顶元素
void* Top_SeqStack(SeqStack* stack)
{
	if (stack == NULL)
	{
		return NULL;
	}
	if (stack->size == 0)
	{
		return NULL;
	}

	return stack->data[stack->size - 1];
}
//出栈
void Pop_SeqStack(SeqStack* stack)
{
	if (stack == NULL)
	{
		return;
	}
	if (stack->size == 0)
	{
		return;
	}

	//出栈
	stack->data[stack->size - 1] = NULL;
	stack->size--;
}
//判断是否为空
int IsEmpty(SeqStack* stack)
{
	if (stack == NULL)
	{
		return -1;
	}
	if (stack->size == 0)
	{
		return SEQSTACK_TRUE;
	}

	return SEQSTACK_FLAST;
}
//返回栈中的元素个数
int Size_SeqStack(SeqStack* stack)
{
	return stack->size;
}
//释放
void FreeSpace(SeqStack* stack)
{
	if (stack != NULL)
	{
		free(stack);
	}
}
