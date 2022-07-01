#include<stdio.h>
#include<Windows.h>


//存储怪物信息
class Monster
{
public:
	int ID;
	int Level;
	char Name[20];
public:
	Monster() {}
	Monster(int ID, int Level, const char* Name)
	{
		this->ID = ID;
		this->Level = Level;
		memcpy(&this->Name, Name, strlen(Name) + 1);
	}
};

//存储树的节点
template<class T>
class TreeNode {
public:
	T element;					//当前节点存储的数据  		
	TreeNode<T>* pLeft;			//指向左子节点的指针			
	TreeNode<T>* pRight;		//指向右子节点的指针			

	TreeNode(T& ele) {
		//初始化Node节点							
		memset(&element, 0, sizeof(TreeNode));
		//为元素赋值							
		memcpy(&element, &ele, sizeof(T));
		pLeft = pRight = NULL;
	}
};

template<class T>
class BSortTree {
public:
	BSortTree();					//构造函数			
	~BSortTree();					//析构函数			
public:
	void InOrderTraverse(TreeNode<T>* pNode);			//中序遍历			
	void PreOrderTraverse(TreeNode<T>* pNode);			//前序遍历			
	void PostOrderTraverse(TreeNode<T>* pNode);			//后序遍历			
	TreeNode<T>* GetRoot();								//返回根节点			
	int GetDepth(TreeNode<T>* pNode);					//返回某个节点的高度/深度			
private:
	void Init();   //初始化怪物信息
	void Clear(TreeNode<T>* pNode);  //用于释放堆区
private:
	TreeNode<T>* m_pRoot;		//根结点指针			
	int size;					//树中元素总个数			
};


int main()
{
	TreeNode<Monster>* m_pRoot = NULL;
	TreeNode<Monster>* m_pRoot2 = NULL;
	BSortTree<Monster> Bin;

	m_pRoot = Bin.GetRoot();
	Bin.GetDepth(m_pRoot);

	printf("----------------先序 ----------------\n");
	Bin.PreOrderTraverse(m_pRoot);
	printf("---------------- 中序 ----------------\n");
	Bin.InOrderTraverse(m_pRoot);
	printf("----------------后序----------------\n");
	Bin.PostOrderTraverse(m_pRoot);

	return 0;
}



template<class T>
BSortTree<T>::BSortTree()
{
	Init();
}

template<class T>
BSortTree<T>::~BSortTree() {

	//释放所以节点空间								
	Clear(m_pRoot);
}
template<class T>
void BSortTree<T>::Clear(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return;
	}
	//先删除左子树
	Destory(pNode->pLeft);
	//在删除右子树
	Destory(pNode->pRight);
	delete pNode;
	pNode = NULL:
}

template<class T>
void BSortTree<T>::Init()
{
	//创建怪物信息
	Monster m1(1, 1, "刺猬");
	Monster m2(2, 2, "野狼");
	Monster m3(3, 3, "野猪");
	Monster m4(4, 4, "士兵");
	Monster m5(5, 5, "火龙");
	Monster m6(6, 6, "独角兽");
	Monster m7(7, 7, "江湖大盗");

	//创建 树节点
	TreeNode<Monster>* n1 = new TreeNode<Monster>(m1);
	TreeNode<Monster>* n2 = new TreeNode<Monster>(m2);
	TreeNode<Monster>* n3 = new TreeNode<Monster>(m3);
	TreeNode<Monster>* n4 = new TreeNode<Monster>(m4);
	TreeNode<Monster>* n5 = new TreeNode<Monster>(m5);
	TreeNode<Monster>* n6 = new TreeNode<Monster>(m6);
	TreeNode<Monster>* n7 = new TreeNode<Monster>(m7);

	//二叉树赋值
	m_pRoot = n5;
	n5->pLeft = n4;
	n5->pRight = n6;
	n4->pLeft = n1;
	n1->pRight = n2;
	n6->pLeft = n3;
	n3->pRight = n7;
	size = 7;
}

//返回根节点
template<class T>
TreeNode<T>* BSortTree<T>::GetRoot()
{
	return m_pRoot;
}

//返回某个节点的高度/深度			
template<class T>
int BSortTree<T>::GetDepth(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return 0;
	}
	else
	{
		//先序遍历
		int m = GetDepth(pNode->pLeft);
		int n = GetDepth(pNode->pRight);
		return (m > n) ? (m + 1) : (n + 1);
	}
}

//中序遍历所有怪物,列出怪的名字
template<class T>
void BSortTree<T>::InOrderTraverse(TreeNode<T>* pNode)
{

									
	if (pNode == NULL)
	{
		return;
	}

	// 先左 在根 在右
	InOrderTraverse(pNode->pLeft);
	printf("怪名：%s \n", pNode->element.Name);
	InOrderTraverse(pNode->pRight);
}

//先序遍历所有怪物,列出怪的名字		
template<class T>
void BSortTree<T>::PreOrderTraverse(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return;
	}
	// 先根 在左 在右
	printf("怪名：%s \n", pNode->element.Name);
	PreOrderTraverse(pNode->pLeft);
	PreOrderTraverse(pNode->pRight);
}

//后序遍历所有怪物,列出怪的名字								
template<class T>
void BSortTree<T>::PostOrderTraverse(TreeNode<T>* pNode)
{

	if (pNode == NULL)
	{
		return;
	}

	// 先左 在右 在根
	PostOrderTraverse(pNode->pLeft);
	PostOrderTraverse(pNode->pRight);
	printf("怪名：%s \n", pNode->element.Name);
}

