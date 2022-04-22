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

int CaculateTreeDpth(BinaryNode* root)
{
	if (root == NULL)
	{
		return;
	}

	int depth = 0;
	//求左子树的高度
	int leftDepth = CaculateTreeDpth(root->lchild);
	int rightDepth = CaculateTreeDpth(root->rchild);
	depth = leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;

	return depth;
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

	int depth = CaculateTreeDpth(&node1);
	printf("树的高度为:%d\n", depth);

}

int main()
{
	CresteBinaryTree();
	
	system("pause");
	return 0;
}