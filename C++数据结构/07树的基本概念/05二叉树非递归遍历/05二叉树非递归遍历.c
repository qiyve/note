#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"LinkStack.h"

#define MY_FALSE 0
#define MY_TRUE 1


//二叉树结点
typedef struct BINARYNODE {
	char ch;//根
	struct BINARYNODE* lchild; //左
	struct BINARYNODE* rchild; //右
}BinaryNode;


typedef struct BITREESTACKNODE
{
	LinkNode node; 
	BinaryNode* root; //结点指针
	int flag; //控制可读或不读

}BitreeStackNode;

//创建栈中的结点
BitreeStackNode* CreateBiTreeStackNode(BinaryNode* node, int flag)
{
	BitreeStackNode* newnode = (BitreeStackNode*)malloc(sizeof(BitreeStackNode));
	newnode->root = node;
	newnode->flag = flag;

	return newnode;
}


//二叉树的非递归遍历
void NonRecursion(BinaryNode* root)
{
	//创建栈
	LinkStack* stack = Init_LinkStack();
	//把根节点放到栈中
	Push_LinkStack(stack, (LinkNode*)CreateBiTreeStackNode(root, MY_FALSE));

	while (Size_LinkStack(stack) > 0)
	{
		//先弹出栈顶元素
		BitreeStackNode* node = (BitreeStackNode*)Top_LinkStack(stack);
		Pop_LinkStack(stack);

		//判断弹出的节点是否为空
		if (node->root == NULL)
		{
			continue;
		}

		//判断节点的标志
		if (node->flag == MY_TRUE)
		{
			printf("%c", node->root->ch);
		}
		else
		{
			//当前结点的右节点入栈
			Push_LinkStack(stack, (LinkNode*)CreateBiTreeStackNode(node->root->rchild, MY_FALSE));
			//当前结点的左节点入栈
			Push_LinkStack(stack, (LinkNode*)CreateBiTreeStackNode(node->root->lchild, MY_FALSE));
			//当前节点入栈  并修改标志
			node->flag = MY_TRUE;
			Push_LinkStack(stack, (LinkNode*)node);
		}
	}

}

//递归遍历
void Recursion(BinaryNode* root)
{
	if (root == NULL)
	{
		return;
	}

	//先序排序
	printf("%c", root->ch);
	//在左子树
	Recursion(root->lchild);
	Recursion(root->rchild);
}

void CresteBinaryTree()
{
	//创建结点
	BinaryNode node1 = { 'A',NULL,NULL };
	BinaryNode node2 = { 'B',NULL,NULL };
	BinaryNode node3 = { 'C',NULL,NULL };
	BinaryNode node4 = { 'D',NULL,NULL };
	BinaryNode node5 = { 'E',NULL,NULL };
	BinaryNode node6 = { 'F',NULL,NULL };
	BinaryNode node7 = { 'G',NULL,NULL };
	BinaryNode node8 = { 'H',NULL,NULL };
	

	//建立结点关系
	node1.lchild = &node2;
	node1.rchild = &node6;
	node2.rchild = &node3;
	node3.lchild = &node4;
	node3.rchild = &node5;
	node6.rchild = &node7;
	node7.lchild = &node8;

	//二叉树的非递归打印
	NonRecursion(&node1);
	printf("\n");
	//递归遍历
	Recursion(&node1);
	printf("\n");

}

int main()
{
	CresteBinaryTree();
	

	system("pause");
	return 0;
}