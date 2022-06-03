#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

DWORD ReadPEFile(IN LPSTR lpszFile, OUT LPVOID* pFileBuffer)
{
	// 下面有个IN和OUT，大致意思就是参数的类型传入进来之后不进行宏扩展；
	//啥也不干，即使理解成干，也是扩展成空白，这个是C++语法中允许的；
	//LPSTR  ---->  typedef CHAR *LPSTR, *PSTR; 意思就是char* 指针；在WINNT.H头文件里面
	// typedef unsigned long       DWORD;  DWORD是无符号4个字节的整型
	//LPVOID ---->  typedef void far *LPVOID;在WINDEF.H头文件里面；别名的void指针类型

	FILE* pFile = NULL;
	DWORD fileSize = 0;
	LPVOID pTempFileBuffer = NULL;

	//打开文件
	pFile = fopen(lpszFile, "rb"); 
	if (!pFile)
	{
		printf("代开文件失败\n");
		return 0;
	}

	/*
     关于在指针类型中进行判断的操作，下面代码出现的情况和此一样，这里解释下：
     1.因为指针判断都要跟NULL比较，相当于0，假值，其余都是真值
     2.if(!pFile)和if(pFile == NULL), ----> 为空，就执行语句；这里是两个等于号不是一个等于号
     3.if(pFile)就是if(pFile != NULL), 不为空，就执行语句；
     */

	//读取文件内容后，获取文件大小
	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	/*
	*  fseek 通过使用二进制的方式打开文件，移动文件读写指针的位置,在stdio.h头文件里
	int fseek(FILE * stream, long offset, int fromwhere);
	上面是fseek的函数原型
	第一个参数stream 为文件指针
	第二个参数offset 为偏移量，整数表示正向偏移，负数表示负向偏移
	第三个参数fromwhere 为指针的起始位置, 设定从文件的哪里开始偏移, 可能取值为：SEEK_CUR，SEEK_END，SEEK_SET
	SEEK_SET 0 文件开头
	SEEK_CUR 1 当前读写的位置
	SEEK_END 2 文件尾部*/

	//申请空间
	pTempFileBuffer = malloc(fileSize);
	if (!pTempFileBuffer)
	{
		printf("内存分配失败\n");
		fclose(pFile);
		return 0;
	}

	//根据申请到的内存空间，读取数据
	size_t n = fread(pTempFileBuffer, fileSize, 1, pFile);
	if (!n)
	{
		printf("读取数据失败\n");
		free(pTempFileBuffer);  
		fclose(pFile);

		return 0;
    }

	//数据读取成功，关闭文件
	*pFileBuffer = pTempFileBuffer;// 将读取成功的数据所在的内存空间的首地址放入指针类型pFileBuffer
	fclose(pFile);                 //关闭文件

	return fileSize;               //返回获取文件的大小
}

//通过复制FileBuffer并增加1000H到新的ImageBuffer里面
DWORD CopyFileBufferToNewImageBuffer(IN LPVOID pFileBuffer, IN size_t fileSize, OUT LPVOID* pNewImageBuffer)
{
	PIMAGE_DOS_HEADER			pDos  = NULL;
	PIMAGE_NT_HEADERS			pNt	  = NULL;
	PIMAGE_FILE_HEADER			pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32	pOp   = NULL;
	PIMAGE_SECTION_HEADER		pSect = NULL;
	PIMAGE_SECTION_HEADER		pLastSect = NULL;
	LPVOID pTempNewImageBuffer	= 0;
	DWORD	sizeOfFile = 0;
	DWORD  numberOfSection = 0;
	DWORD  okAddSections = 0;

	//判断读取pFileBuffer读取是否成功
	if (!pFileBuffer)
	{
		printf("pFileBuffer缓冲区指针无效\n");
		return 0;
	}

	//判断是否为MZ标志
	if ((*(PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE) // IMAGE_DOS_SIGNATURE --> MZ
	{
		printf("不是有效MZ标记\n");
		return 0;
	}

	//判断是否是PE标记
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*(PWORD)((DWORD)pDos + pDos->e_lfanew) != IMAGE_NT_SIGNATURE) // IMAGE_NT_SIGNATURE --> PE
	{
		printf("不是有效PE标记\n");
		return 0;
	}

	//*********************申请开辟内存空间*****************************************************************

	sizeOfFile = fileSize + 0x1000;
	pTempNewImageBuffer = malloc(sizeOfFile);

	//判断内存空间是否开辟成功
	if (!pTempNewImageBuffer)
	{
		printf("pTempNewImageBuffer分配内存失败\n");
		return 0;
	}

	//初始化内存内容
	memset(pTempNewImageBuffer, 0, sizeOfFile);

	//定位Dos地址
	pDos = (PIMAGE_DOS_HEADER)(pTempNewImageBuffer);
	//NT头
	pNt = (PIMAGE_NT_HEADERS)((DWORD)pDos + pDos->e_lfanew);
	//PE头
	pPE = (PIMAGE_FILE_HEADER)(((DWORD)pNt) + 0x04);
	//可选PE头
	pOp = (PIMAGE_OPTIONAL_HEADER32)(((DWORD)pPE) + IMAGE_SIZEOF_FILE_HEADER); //IMAGE_SIZEOF_FILE_HEADER -> 20个字节
	
   //第一个节表地址
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOp + pPE->SizeOfOptionalHeader);

	//最后一个节表地址
	pLastSect = &pSect[pPE->NumberOfSections - 1];

	// 判断是否有足够的空间添加一个节表
		//判断条件：
		/*
		SizeOfHeader - (DOS + 垃圾数据 + PE标记 + 标准PE头 + 可选PE头 + 已存在节表) >= 2个节表的大小
		SizeOfHeader在可选PE头里面
		 */

	okAddSections = (DWORD)(pOp->SizeOfHeaders - (pDos->e_lfanew + 0x04 + sizeof(PIMAGE_FILE_HEADER))
		+ pPE->SizeOfOptionalHeader + sizeof(PIMAGE_SECTION_HEADER) * pPE->NumberOfSections);

	if (okAddSections <= 2 * sizeof(PIMAGE_SECTION_HEADER))
	{
		printf("这个exe文件头部剩余空间不够\n");
		free(pTempNewImageBuffer);
		return 0;
	}

	//上面没问题，就开始修改内容了
	//*************************修改内容*******************************************************************

	 //初始化新节表信息
	PWORD pNumberOfSecton = &pPE->NumberOfSections;
	PDWORD pSizeOfImage = &pOp->SizeOfImage;
}