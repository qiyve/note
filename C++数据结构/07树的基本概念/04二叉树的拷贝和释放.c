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

//遍历二叉树
void Recursion(BinaryNode* root)
{
	if (root == NULL)
	{
		return;
	}

	//先序遍历
	printf("%c", root->ch);
	//遍历左子树
	Recursion(root->lchild);
	//遍历右子树
	Recursion(root->rchild);
}

//拷贝二叉树
BinaryNode* CopyBinaryTree(BinaryNode* root)
{
	if (root == NULL)
	{
		return NULL;
	}

	//拷贝左子树
	BinaryNode* lchild = CopyBinaryTree(root->lchild);
	//拷贝右子树
	BinaryNode* rchild = CopyBinaryTree(root->rchild);

	//创建结点
	BinaryNode* newnode = (BinaryNode*)malloc(sizeof(BinaryNode));
	newnode->ch = root->ch;
	newnode->lchild = lchild;
	newnode->rchild = rchild;

	return newnode;
}

//释放二叉树内存
void FreeSpaceBinaryTree(BinaryNode* root)
{
	if (root == NULL)
	{
		return;
	}
	//释放左子树
	FreeSpaceBinaryTree(root->lchild);
	//释放右子树
	FreeSpaceBinaryTree(root->rchild);

	//释放当前结点
	free(root);

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

	//拷贝
	BinaryNode* root = CopyBinaryTree(&node1); 
	//遍历
	Recursion(root);
	//释放
	FreeSpaceBinaryTree(root);
}

int main()
{
	CresteBinaryTree();
	printf("\n");

	system("pause");
	return 0;
}