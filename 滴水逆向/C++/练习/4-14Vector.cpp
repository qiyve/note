#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

#define SUCCESS           		   1 // 成功					
#define ERROR            		  -1 // 失败					
#define MALLOC_ERROR			  -2 // 申请内存失败					
#define INDEX_ERROR		 		  -3 // 错误的索引号	



template <class T_ELE>
class Vector
{
public:
	Vector();
	Vector(DWORD dwSize);
	~Vector();
public:
	DWORD	at(DWORD dwIndex, OUT T_ELE* pEle);			//根据给定的索引得到元素	
	DWORD   push_back(T_ELE Element);					//将元素存储到容器最后一个位置	
	VOID	pop_back();									//删除最后一个元素	
	DWORD	insert(DWORD dwIndex, T_ELE Element);		//向指定位置新增一个元素	
	DWORD	capacity();									//返回在不增容的情况下，还能存储多少元素	
	VOID	clear();									//清空所有元素	
	BOOL	empty();									//判断Vector是否为空 返回true时为空	
	DWORD	erase(DWORD dwIndex);						//删除指定元素	
	DWORD	size();										//返回Vector元素数量的大小	
private:
	BOOL	expand();
private:
	DWORD  m_dwIndex;					//下一个可用索引	
	DWORD  m_dwIncrement;				//每次增容的大小	
	DWORD  m_dwLen;						//当前容器的长度	
	DWORD  m_dwInitSize;		  	    //默认初始化大小	
	T_ELE* m_pVector;					//容器指针	
};

//初始化
template <class T_ELE>
Vector<T_ELE>::Vector()
	:m_dwInitSize(100), m_dwIncrement(5)
{
	//1.创建长度为m_dwInitSize个T_ELE对象							
	m_pVector = new T_ELE[m_dwInitSize];

	//2.将新创建的空间初始化							
	memset(m_pVector, 0, sizeof(T_ELE) * m_dwInitSize);

	//3.设置其他值						
	m_dwIndex = 0;
	m_dwLen = m_dwInitSize;  //长度
}

//初始化
template <class T_ELE>
Vector<T_ELE>::Vector(DWORD dwSize)
	:m_dwIncrement(5)
{
	//1.创建长度为dwSize个T_ELE对象		
	m_pVector = new T_ELE[dwSize];

	//2.将新创建的空间初始化		
	memset(m_pVector, 0, sizeof(T_ELE) * dwSize);
	//3.设置其他值		
	m_dwIndex = 0;
	m_dwLen = dwSize;
}	

//析构
template <class T_ELE>
Vector<T_ELE>::~Vector()
{
	//释放空间 delete[]		
	delete[] m_pVector;
	m_pVector = NULL;

}

// 扩充容量
template <class T_ELE>
BOOL Vector<T_ELE>::expand()
{
	DWORD dwLenTemp = 0;
	T_ELE* pVectorTemp = NULL;

	// 1. 计算增加后的长度							
	dwLenTemp = m_dwLen + m_dwIncrement;
	// 2. 申请空间	
	pVectorTemp = new T_ELE[dwLenTemp];
	memset(pVectorTemp, 0, sizeof(T_ELE) * dwLenTemp);
	// 3. 将数据复制到新的空间							
	memcpy(pVectorTemp, m_pVector, sizeof(T_ELE) * m_dwLen);
	// 4. 释放原来空间							
	delete[] m_pVector;
	m_pVector = pVectorTemp;
	pVectorTemp = NULL;
	// 5. 为各种属性赋值							
	m_dwLen = dwLenTemp;

	return true;
}

// 尾插
template <class T_ELE>
DWORD  Vector<T_ELE>::push_back(T_ELE Element)
{
	//1.判断是否需要增容，如果需要就调用增容的函数							
	if (m_dwIndex >= m_dwLen)
	{
		expand();
	}

	//2.将新的元素复制到容器的最后一个位置							
	memcpy(&m_pVector[m_dwIndex], &Element, sizeof(T_ELE));

	//3.修改属性值							
	m_dwIndex++;

	return SUCCESS;
}

//指定插入
template <class T_ELE>
DWORD  Vector<T_ELE>::insert(DWORD dwIndex, T_ELE Element)
{
	//1.判断索引是否在合理区间							
	if (dwIndex<0 || dwIndex>m_dwIndex)
	{
		return INDEX_ERROR;
	}
	//2.判断是否需要增容，如果需要就调用增容的函数							
	if (m_dwIndex >= m_dwLen)
	{
		expand();
	}
	//3.将dwIndex只后的元素后移							
	for (DWORD i = m_dwIndex; i > dwIndex; i--)
	{
		memcpy(&m_pVector[i], &m_pVector[i-1], sizeof(T_ELE));
	}

	//4.将Element元素复制到dwIndex位置		
	memcpy(&m_pVector[dwIndex], &Element, sizeof(T_ELE));
	//5.修改属性值	
	m_dwIndex++;

	return SUCCESS;
}


template <class T_ELE>
DWORD Vector<T_ELE>::at(DWORD dwIndex, OUT T_ELE* pEle)
{
	//判断索引是否在合理区间							
	if (dwIndex<0 || dwIndex>= m_dwIndex)
	{
		return INDEX_ERROR;
	}

	//将dwIndex的值复制到pEle指定的内存							
	memcpy(pEle, &m_pVector[dwIndex], sizeof(T_ELE));
	return SUCCESS;
}

//删除最后一个元素		
template<class T_ELE>
VOID Vector<T_ELE>::pop_back()                  
{
	// m_dwIndex 下一个可用的索引  --m_dwIndex 即上一个索引 也就是最后一个元素 
	memset(&m_pVector[m_dwIndex - 1], 0, sizeof(T_ELE));
	m_dwIndex--;
	
}


//返回在不增容的情况下，还能存储多少元素	
template<class T_ELE>
DWORD Vector<T_ELE>::capacity()
{
	DWORD capacity = 0;   //总长度 - 下一个索引
	capacity = m_dwLen - m_dwIndex;

	return capacity;
}

//判断Vector是否为空 返回true时为空	
template<class T_ELE>
BOOL Vector<T_ELE>::empty()
{
	if (m_dwIndex != 0 || m_pVector != NULL)
	{
		return SUCCESS;
	}

	return ERROR;
}

//清空所有元素
template<class T_ELE>
VOID Vector<T_ELE>::clear()
{
	//全部初始化为 0 
	memset(m_pVector, 0, sizeof(T_ELE) * m_dwIndex);
	m_dwIndex = 0;
	m_dwLen = 0;

	delete[] m_pVector;
	m_pVector = NULL;
}

//删除指定元素	
template<class T_ELE>
DWORD Vector<T_ELE>::erase(DWORD dwIndex)
{
	
	//判断该值是否 合理
	if (dwIndex<0 || dwIndex>m_dwIndex)
	{
		return INDEX_ERROR;
	}
	//遍历查找  
	for (DWORD i = dwIndex; i < m_dwIndex; i++)
	{
		memcpy(&m_pVector[i], &m_pVector[i + 1], sizeof(T_ELE));
	}
	m_dwIndex--; //更新索引

	return SUCCESS;

}

//返回Vector元素数量的大小
template<class T_ELE>
DWORD Vector<T_ELE>::size()
{
	return m_dwIndex-1;
}

void TestVector()
{
	int sum = 0;
	Vector<int>* pVector = new Vector<int>(5);

	//插入
	pVector->push_back(1);
	pVector->push_back(2);
	pVector->push_back(3);
	pVector->push_back(4);
	pVector->push_back(5);

	pVector->insert(3, 7);

	pVector->pop_back();
	pVector->erase(2);
}

int main()
{
	TestVector();

	return 0;
}


