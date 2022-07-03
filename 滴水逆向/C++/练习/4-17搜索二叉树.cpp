#include<stdio.h>
#include<Windows.h>

#define SUCCESS           1 // 执行成功						
#define ERROR			 -1 // 执行失败			         			

template<class T>
class TreeNode {
public:
	T element;					//当前节点存储的数据			
	TreeNode<T>* pLeft;			//指向左子节点的指针			
	TreeNode<T>* pRight;		//指向右子节点的指针			
	TreeNode<T>* pParent;		//指向父结点的指针			


	TreeNode(T& ele) {
		//初始化Node节点							
		memset(&element, 0, sizeof(TreeNode));
		//为元素赋值							
		memcpy(&element, &ele, sizeof(T));
		pLeft = pRight = pParent = NULL;
	}
	//重载== 比较两结点是否相等								
	bool operator==(TreeNode<T>* node) {
		return node->element == element ? true : false;
	}
};

template<class T>
class BSortTree {
public:
	BSortTree();						//构造函数		
	~BSortTree();						//析构函数		
public:									//判断树是否为空		
	bool IsEmpty();						//新增节点		
	DWORD Insert(T element);							//删除节点		
	void Delete(T element);								
	TreeNode<T>* Search(T element);						//查找节点		
	void InOrderTraverse(TreeNode<T>* pNode);						//中序遍历		
	void PreOrderTraverse(TreeNode<T>* pNode);						//前序遍历		
	void PostOrderTraverse(TreeNode<T>* pNode);						//后序遍历		
private:
	TreeNode<T>* GetMaxNode(TreeNode<T>* pNode);						//获取以pNode为根的最大节点		
	TreeNode<T>* GetMinNode(TreeNode<T>* pNode);						//获取以pNode为根的最小节点		
	TreeNode<T>* SearchNode(TreeNode<T>* pNode, T element);				//获取以pNode为根的最小节点		
	DWORD InsertNode(T element, TreeNode<T>* pNode);					//新增节点		
	TreeNode<T>* DeleteNode(T element, TreeNode<T>* pNode);				//删除节点		
	void Clear(TreeNode<T>* pNode);					//清空所有节点		
private:
	TreeNode<T>* m_pRoot;							//根结点指针		
	int size;										//树中元素总个数		
};


void test()
{
}

int main()
{


	return 0;
}

template<class T>
BSortTree<T>::BSortTree()
{
	m_pRoot = NULL;
	size = 0;
}

template<class T>
BSortTree<T>::~BSortTree() {

	Clear(m_pRoot);
}


template<class T>
DWORD BSortTree<T>::Insert(T element)
{
	//如果根节点为空								
	if (!m_pRoot)
	{
		m_pRoot = new TreeNode<T>(element);
		size++;
		return SUCCESS;
	}
	//如果根节点不为空								
	return InsertNode(element, m_pRoot);
}

template<class T>
DWORD BSortTree<T>::InsertNode(T element, TreeNode<T>* pNode)
{
	//将元素封装到节点中								
	TreeNode<T>* pNewNode = new TreeNode<T>(element);
	//如果element == 当前节点 直接返回								
	if (element == pNode->element)
	{
		return SUCCESS;
	}
	//如果pNode的左子树为NULL 并且element < 当前节点								
	if (pNode->pLeft == NULL && element < pNode->element)
	{
		pNode->pLeft = pNewNode;
		pNewNode->pParent = pNode;
		size++;
		return SUCCESS;
	}
	//如果pNode的右子树为NULL 并且element > 当前节点								
	if (pNode->pRight == NULL && element > pNode->element) {
		pNode->pRight = pNewNode;
		pNewNode->pParent = pNode;
		size++;
		return SUCCESS;
	}
	//如果element<当前节点 且当前节点的左子树不为空								
	if (element < pNode->element)
	{
		InsertNode(element, pNode->pLeft);
	}
	else
	{
		InsertNode(element, pNode->pRight);
	}
	return SUCCESS;
}

template<class T>
void BSortTree<T>::Clear(TreeNode<T>* pNode)
{
	if (pNode != NULL)
	{
		Clear(pNode->pLeft);
		Clear(pNode->pRight);
		delete pNode;
		pNode = NULL;
	}
}

template<class T>
bool BSortTree<T>::IsEmpty()
{
	return size == 0 ? true : false;
}

template<class T>
TreeNode<T>* BSortTree<T>::Search(T element)
{
	return SearchNode(m_pRoot, element);
}

template<class T>
TreeNode<T>* BSortTree<T>::SearchNode(TreeNode<T>* pNode, T element)
{
	if (pNode == NULL)					//如果节点为NULL			
	{
		return NULL;
	}
	else if (element == pNode->element)					//如果相等			
	{
		return pNode;
	}					//如果比节点的元素小 向左找			
	else if (element < pNode->element)
	{
		return SearchNode(pNode->pLeft, element);
	}
	else				//如果比节点的元素大 向右找			
	{
		return SearchNode(pNode->pRight, element);
	}
}

template<class T>
void BSortTree<T>::Delete(T element)
{
	if (m_pRoot == NULL)
	{
		return ERROR;
	}
	DeleteNode(element, m_pRoot);
}

template<class T>
TreeNode<T>* BSortTree<T>::DeleteNode(T element, TreeNode<T>* pNode)
{
	// 空树
	if (m_pRoot == NULL)
	{
		return ERROR;
	}

	else if (element == pNode->element)
	{
		//1、 只有左子树  没有右子树
		if (pNode->pLeft != NULL && pNode->pRight == NULL)
		{
			TreeNode<T>* pPt = pNode->pParent;//获取 当前节点 的 父节点
			pPt->pLeft = pNode->pLeft;        // 用父节点的左子树 直接 指向当前节点的左子树
			delete pNode;
		}
		//2、 左子树为空  只有右子树
		else if (pNode->pLeft == NULL && pNode->pRight != NULL)
		{
			TreeNode<T>* pPt = pNode->pParent; //获取 当前节点 的 父节点
			pPt->pRight = pNode->pRight;	  // 用父节点的右子树 直接 指向当前节点的右子树
			delete pNode;
		}
		
		//3、左右子树都为空
		else if (pNode->pLeft == NULL && pNode->pRight == NULL)
		{
			TreeNode<T>* p;
			p = pNode->pParent;
			if (p->pLeft != NULL && p->pRight == NULL) //这里实际意义就是看当前节点在父节点的左边还是右边
			{
				delete p->pLeft;
				p->pLeft == NULL;
			}
			if (p->pLeft == NULL && p->pRight != NULL)
			{
				delete p->pRight;
				p->pRight = NULL;
			}

			delete p->pRight;
			p->pRight = NULL;  //这两行就是代表子节点一样，且不为空，删除哪个都一样。
		}

		//左右子树均不为空
		else if (pNode->pLeft != NULL && pNode->pRight != NULL)
		{
			TreeNode<T>* pCurrent = pNode->pRight;

			//GetMinNode是一个递归函数，返回NODE子树里的最小节点
			TreeNode<T>* pMin = GetMinNode(pNode->pRight);

			//把最小的节点元素抬到pNode节点这里来
			pNode->element = (int)pMin;

			//此时此刻，Pnode已经替换为最小节点的元素了，
			//那么只需要删除pCurrent（pNode->pRight）下的子树最小节点就可以了，这里用的递归。
			DeleteNode(pNode->element, pCurrent);
		}
	}
	else if (element > pNode->element)
	{
		//Element 大于pNode的 值。那么就往Pnode右树开始找
		DeleteNode(element, pNode->pRight);
	}
	else
	{
		DeleteNode(element, pNode->pLeft);
	}

	return NULL;
}

template<class T>
TreeNode<T>* BSortTree<T>::GetMinNode(TreeNode<T>* pNode)
{
	TreeNode<T>* pMin = NULL;
	if (pNode != NULL)
	{
		/*说一下，这里为什么不用T类型，因为T代表整个类型大小，但是我们只需要NODE头4个字节的数据,
		这里有一点不通用，节点的头四个字节数据类型被限制了。*/
		int data = pNode->element;
		if (data >= pNode->element)
		{
			pMin = (TreeNode<T>*)pNode->element;//把下一个比较小的节点存起来
		}

		GetMinNode(pNode->pLeft);
		return pMin;
	}
}

//中序遍历	
template<class T>
void BSortTree<T>::InOrderTraverse(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return ERROR;
	}
	InOrderTraverse(pNode->pLeft);
	printf("%d\n", pNode->element);
	InOrderTraverse(pNode->pRight);
}

//先序遍历	
template<class T>
void BSortTree<T>::PreOrderTraverse(TreeNode<T>* pNode)
{
	if (pNode == NULL)
	{
		return ERROR;
	}
	printf("%d\n", pNode->element);
	PreOrderTraverse(pNode->pLeft);
	PreOrderTraverse(pNode->pRight);

}

//后序遍历	
template<class T>
void BSortTree<T>::PostOrderTraverse(TreeNode<T>* pNode)				
{
	if (pNode == NULL)
	{
		return ERROR;
	}
	PostOrderTraverse(pNode->pLeft);
	PostOrderTraverse(pNode->pRight);
	printf("%d\n", pNode->element);
}
