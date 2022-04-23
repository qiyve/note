#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//二叉树结点
typedef struct BINARYNODE {
	char ch;//根
	struct BINARYNODE* lchild; //左
	struct BINARYNODE* rchild; //右
}BinaryNode;

void Recursion(BinaryNode* root)
{
	if (root == NULL)
	{
		return;
	}
	printf("%c", root->ch);
	Recursion(root->lchild);
	Recursion(root->rchild);
}

BinaryNode* CreateBinaryTree()
{
	fflush(stdin); //清空文件缓存区
	char ch;
	scanf("%c", &ch);

	//定义结点
	BinaryNode* node;
	//BinaryNode* lchild;
	//BinaryNode* rchild;


	if (ch == '#')
	{
		node = NULL;
	}

	else
	{
	/*	lchild = CreatBinaryTree();
		rchild = CreatBinaryTree();*/

		//创建结点
		node = (BinaryNode*)malloc(sizeof(BinaryNode));
		node->ch = ch;
		node->lchild = CreateBinaryTree();
		node->rchild = CreateBinaryTree();
	}

	return node;
}


int main()
{
	//创建树
	BinaryNode* root = CreateBinaryTree();
	//打印树
	Recursion(root);
	
	system("pause");
	return 0;
}