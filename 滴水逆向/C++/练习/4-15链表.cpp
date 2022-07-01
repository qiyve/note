#include<stdio.h>
#include<Windows.h>


#define SUCCESS           1 // 执行成功											
#define ERROR            -1 // 执行失败											
#define INDEX_IS_ERROR   -2 // 错误的索引号											
#define BUFFER_IS_EMPTY  -3 // 缓冲区已空

template<class T_ELE> 
class NODE{
public:
	T_ELE Data;        
	NODE<T_ELE>* pNext;
};

template <class T_ELE>
class LinkedList :public NODE<T_ELE>
{
public:
	LinkedList();                           //默认构造函数
	~LinkedList();
public:
	BOOL  IsEmpty();											//判断链表是否为空 空返回1 非空返回0				
	DWORD  Clear();												//清空链表				
	DWORD GetElement(IN DWORD dwIndex, OUT T_ELE& Element);		//根据索引获取元素				
	DWORD GetElementIndex(IN T_ELE& Element);					//根据元素获取链表中的索引				
	DWORD Insert(IN T_ELE Element);								//新增元素				
	DWORD Insert(IN DWORD dwIndex, IN T_ELE Element);			//根据索引新增元素				
	DWORD Delete(IN DWORD dwIndex);								//根据索引删除元素				
	DWORD GetSize();											//获取链表中元素的数量
	VOID Show_Linke();												//打印链表		
private:
	NODE<T_ELE>* m_head;					//链表头指针，指向第一个节点				
	DWORD m_dwLength;						//元素的数量				
};

//测试
void test()
{
	LinkedList<int>Link;

	int index = 3;
	int value = 0;
	int element = 10;

	Link.Insert(0, 40);
	Link.Insert(1, 50);
	Link.Insert(2, 30);
	Link.Insert(3, 10);
	Link.Insert(4, 60);
	//Link.Insert(5, 70);


	//Link.Insert(20);
	//printf("Link.GetElementIndex(%d): %d\n", element, Link.GetElementIndex(element));

	Link.GetElement(index, value);
	printf("Link.GetElement(%d, %d)\n", index, value);

	Link.Delete(5);

	Link.Show_Linke();
}


int main()
{
	test();

	return 0;
}

//无参构造函数 初始化成员									
template<class T_ELE> 
LinkedList<T_ELE>::LinkedList()
	:m_head(NULL), m_dwLength(0)
{

}

//析构函数 清空元素									
template<class T_ELE>
LinkedList<T_ELE>::~LinkedList()
{
	Clear();
}

//判断链表是否为空									
template<class T_ELE>
BOOL LinkedList<T_ELE>::IsEmpty()
{
	if (m_head == NULL || m_dwLength == 0)
	{
		return BUFFER_IS_EMPTY;
	}
	else
	{
		return SUCCESS;
	}
}

//清空链表									
template<class T_ELE> 
DWORD LinkedList<T_ELE>::Clear()
{
	// 1. 判断链表是否为空	
	if (m_head == NULL || m_dwLength == 0)
	{
		return INDEX_IS_ERROR;
	}

	// 2. 循环删除链表中的节点
	NODE<T_ELE>* pHead = m_head;
	for (DWORD i = 0; i < m_dwLength; i++)
	{
		//创建临时指针用释放堆数据
		NODE<T_ELE>* pItertor = pHead;
		pHead = pHead->pNext;   // pHead ->pNext  指向下一个节点
		delete pItertor;
	}
	// 3. 删除最后一个节点并将链表长度置为0
	m_head = NULL;
	m_dwLength = 0;

	return SUCCESS;
}


//根据索引获取元素									
template<class T_ELE> 
DWORD LinkedList<T_ELE>::GetElement(IN DWORD dwIndex, OUT T_ELE& Element)
{
	NODE<T_ELE>* pTempNode = NULL;
	// 1. 判断索引是否有效	
	if (dwIndex<0 || dwIndex>m_dwLength)
	{
		return INDEX_IS_ERROR;
	}
	//2、判断链表是否为空
	if (m_head == NULL || m_dwLength == 0)
	{
		return BUFFER_IS_EMPTY;
	}

	// 3. 取得索引指向的节点
	pTempNode = m_head;
	for (DWORD i = 0; i < dwIndex; i++)
	{
		pTempNode = pTempNode->pNext;
	}

	// 3. 将索引指向节点的值复制到OUT参数	
	memcpy(&Element, &pTempNode->Data, sizeof(T_ELE));

	return SUCCESS;
}


//根据元素内容获取索引									
template<class T_ELE>
DWORD LinkedList<T_ELE>::GetElementIndex(IN T_ELE& Element)
{
	NODE<T_ELE>* pTempNode = NULL;
	//1、判断链表是否为空
	if (m_head == NULL || m_dwLength == 0)
	{
		return BUFFER_IS_EMPTY;
	}
	//2、循环遍历链表，找到与ELement相同的元素
	pTempNode = m_head;
	for (DWORD i = 0; i < m_dwLength; i++)
	{  
		//也可以通过重载 == 来进行比较 
		if (!memcmp(&Element, &pTempNode->Data, sizeof(T_ELE)))
		{
			return i;
		}
		pTempNode = pTempNode->pNext;  
	}
	return ERROR;
}


//在链表尾部新增节点									
template<class T_ELE> 
DWORD LinkedList<T_ELE>::Insert(IN T_ELE Element)
{
	//尾部新增节点
	NODE<T_ELE>* pNewNode = new NODE<T_ELE>;
	memset(pNewNode, 0, sizeof(T_ELE));
	memcpy(&pNewNode->Data, &Element, sizeof(T_ELE));

	// 1. 判断链表是否为空
	if (m_head == NULL || m_dwLength == 0)
	{
		m_head = pNewNode;
		m_dwLength++;
		return SUCCESS;
	}

	// 2. 如果链表中已经有元素则让前一个节点指向它
	NODE<T_ELE>* pTempNode = m_head;
	for (DWORD i = 0; i < m_dwLength - 1; i++)  //m_dwLength - 1 即上一个节点
	{
		pTempNode = pTempNode->pNext;
	}
	pTempNode->pNext = pNewNode;
	m_dwLength++;

	return SUCCESS;
}

//将节点新增到指定索引的位置						0 1 2 3 4			
template<class T_ELE> DWORD
LinkedList<T_ELE>::Insert(IN DWORD dwIndex, IN T_ELE Element)
{
	NODE<T_ELE>* pPreviousNode = NULL;   //上一个 节点
	NODE<T_ELE>* pCurrentNode = NULL;    //当前  节点
	NODE<T_ELE>* pNextNode = NULL;		 //下一个节点

	//添加 节点
	NODE<T_ELE>* pNewNode = new NODE<T_ELE>;
	memset(pNewNode, 0, sizeof(T_ELE));
	memcpy(&pNewNode->Data, &Element, sizeof(T_ELE));

	//  1. 判断索引值是否有效		
	if (dwIndex<0 || dwIndex>m_dwLength)
	{
		return INDEX_IS_ERROR;
	}

	//  2. 判断链表是否为空 并且 索引值为0 直接添加
	if (m_head == NULL || m_dwLength == 0)
	{
		if (dwIndex == 0)
		{		
			m_head = pNewNode;
			m_dwLength++;
			return SUCCESS;
		}
		return BUFFER_IS_EMPTY;
	}

	//  3. 如果索引为0	
	if (dwIndex == 0)
	{
		// 索引为 0 让 node->Next 指向头指针指向的地址  头指针重新指向Node的值
		pNewNode->pNext = m_head;
		m_head = pNewNode;
		m_dwLength++;
		return SUCCESS;
	}

	//  4. 如果索引为链表尾	
	if (dwIndex == m_dwLength)
	{
		pPreviousNode = m_head;
		for (DWORD i = 0; i < dwIndex - 1; i++) //通过循环找到链表尾部的节点
		{
			pPreviousNode = pPreviousNode->pNext;
		}
		pPreviousNode->pNext = pNewNode;
		m_dwLength++;
		return SUCCESS;
	}

	//  5. 如果索引为链表中
	pCurrentNode = m_head;
	for (DWORD i = 0; i < dwIndex - 1; i++) //dwIndex - 1 即要添加节点的位置
	{
		pCurrentNode = pCurrentNode->pNext;
	}
	pNextNode = pCurrentNode->pNext;
	pCurrentNode->pNext = pNewNode;
	pNewNode->pNext = pNextNode;
	m_dwLength++;

	return SUCCESS;
}


//根据索引删除节点									
template<class T_ELE>
DWORD LinkedList<T_ELE>::Delete(IN DWORD dwIndex)
{
	NODE<T_ELE>* pPreviousNode = NULL;   //上一个 节点
	NODE<T_ELE>* pCurrentNode = NULL;    //当前  节点
	NODE<T_ELE>* pNextNode = NULL;		 //下一个节点

	//1、判断是否是有效索引值
	if (dwIndex<0 || dwIndex>m_dwLength)
	{
		return INDEX_IS_ERROR;
	}

	//2、判断链表是否为空
	if (m_head == NULL || m_dwLength == 0)
	{
		return BUFFER_IS_EMPTY;
	}

	//3、如果链表中只有头节点，且要删除头节点
	if (m_dwLength == 1 && dwIndex == 0)
	{
		delete m_head;
		m_head = NULL;
		m_dwLength--;
		return SUCCESS;
	}

	//4、如果要删除的头节点
	if (dwIndex == 0)
	{
		pNextNode = m_head->pNext;
		delete m_head;
		m_head = pNextNode;
		m_dwLength--;
		return SUCCESS;
	}
	//5、该索引在链表内部
	pPreviousNode = m_head;
	for (DWORD i = 0; i < dwIndex - 1; i++)
	{
		pPreviousNode = pPreviousNode->pNext;   //获取 要删除节点的 上一个节点  A
	}
	pCurrentNode = pPreviousNode->pNext;    //获取要删除节点       B  
	pNextNode = pCurrentNode->pNext;        //获取要删除节点的下一个节点     C 
	pPreviousNode->pNext = pNextNode;       //用上一个节点指向 删除节点 的下一个节点   A -> C
	delete pCurrentNode;
	m_dwLength--;

	return SUCCESS;
}

//获取链表中节点的数量									
template<class T_ELE>
DWORD LinkedList<T_ELE>::GetSize()
{
	//判断链表是否为空   不为返回节点数量
	if (m_head == NULL || m_dwLength == 0)
	{
		return BUFFER_IS_EMPTY;
	}

	else
	{
		return m_dwLength;
	}
}


template<class T_ELE> 
VOID LinkedList<T_ELE>::Show_Linke()
{
	if (m_head == NULL || m_dwLength == 0)
	{
		printf("链表为空\n");
	}

	NODE<T_ELE>* pTempNode = m_head;
	for (DWORD i = 0; i < m_dwLength; i++)
	{
		printf("pNode->data: %d\n", pTempNode->Data);
		pTempNode = pTempNode->pNext;
	}
}
