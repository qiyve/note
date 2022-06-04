#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

#define FILEPATH ""

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

	//初始化完成之后，先把为修改的内存空间全部拷贝到新的内存空间
	memcpy(pTempNewImageBuffer, pFileBuffer, fileSize);

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

	//获取节区每个内容的地址
	numberOfSection				= pPE->NumberOfSections;
	PVOID pSecName				= &pSect[numberOfSection].Name;
	PDWORD pSecMisc				= &pSect[numberOfSection].Misc.VirtualSize;
	PDWORD pSecVirtualAddress	= &pSect[numberOfSection].VirtualAddress;;
	PDWORD pSecSizeOfRawData	= &pSect[numberOfSection].SizeOfRawData;
	PDWORD pSecPointToRawData	= &pSect[numberOfSection].PointerToRawData;
	PDWORD pSecCharacteristics	= &pSect[numberOfSection].Characteristics;


	//修改PE文件头里面的节数量信息
	printf("*pNumberOfSection: %x \n", pPE->NumberOfSections);
	*pNumberOfSecton = pPE->NumberOfSections + 1;
	printf("*pNumberOfSection: %x\n", pPE->NumberOfSections);

	//修改PE可选头里面SizeOfImage信息
	printf("*pSizeOfImage:%#X \r\n", pOp->SizeOfImage);
	* pSizeOfImage = pOp->SizeOfImage + 0x1000;
	printf("*pSizeOfImage:%#X \r\n", pOp->SizeOfImage);

	//向节表中添加数据
	memcpy(pSecName, ".newSec", 8);
	*pSecMisc = 0x1000;

	//这里VirtualAddress的地址需要根据最后一个节表中对齐前内存中的实际大小?
	//和文件中对齐后的大小，分别使用VirtualAddress加上她们的值，哪个大，就是
    //哪个；
    //VirtualAddress+max(VirtualSize,SizeOfRawData)
    //就是上面的公式

	//判断出要添加的值   三目运算   
	DWORD add_size = pLastSect->Misc.VirtualSize > pLastSect->SizeOfRawData ? pLastSect->Misc.VirtualSize : pLastSect->SizeOfRawData;

	printf("pLastSectionHeader: %x\n", pLastSect);
	printf("add_size: %x\n", add_size);
	printf("numberOfSection: %x\n", pPE->NumberOfSections);
	printf("pLastSect->Misc.VirtualSize: %x\n", pLastSect->Misc.VirtualSize);
	printf("pLastSect->SizeOfRawData: %x\n", pLastSect->SizeOfRawData);
	printf("add_size: %x\n", add_size);

	//新增节表的地址
	*pSecVirtualAddress = pLastSect->VirtualAddress + add_size;

	//SectionAlignment 对齐   内存
	if (*pSecVirtualAddress % pOp->SectionAlignment)
	{
		*pSecVirtualAddress = *pSecVirtualAddress / pOp->SectionAlignment * pOp->SectionAlignment + pOp->SectionAlignment;
	}

	*pSecSizeOfRawData = 0x1000;
	*pSecPointToRawData = pLastSect->PointerToRawData + pLastSect->SizeOfRawData;

	//FileAlignment 对齐    文件
	if (*pSecPointToRawData % pOp->FileAlignment)
	{
		*pSecPointToRawData = *pSecPointToRawData / pOp->FileAlignment * \
			pOp->FileAlignment + pOp->FileAlignment;
	}

	*pSecCharacteristics = 0x40000040;

	*pNewImageBuffer = pTempNewImageBuffer;
	pTempNewImageBuffer = NULL;

	return sizeOfFile;
}

BOOL MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT LPSTR lpszFile)
{
	FILE* fp = NULL;
	fp = fopen(lpszFile, "wb+");
	if (!fp)
	{
		printf("读取失败\n");
		fclose(fp);
		return FALSE;
	}
	fwrite(pMemBuffer, size, 1, fp);
	fclose(fp);
	fp = NULL;
	return TRUE;
}

VOID NewSectionsInCodeSec()
{
	LPVOID pFileBuffer		 = NULL;
	LPVOID pNewImageBuffer	 = NULL;
	BOOL isOK = FALSE;

	char FilePath1[] = "D:/ipmsg.exe";
	char FilePath2[] = "ipmsg_S.exe";

	DWORD size1 = 0;
	DWORD size2 = 0;

	//File->FileBuffer 

	size1 = ReadPEFile(FilePath1, &pFileBuffer);
	if (size1 == 0 || !pFileBuffer)
	{
		printf("文件-->缓冲区失败\r\n");
		return;
	}
	printf("文件-->缓冲区成功\n");


	//FileBuffer ->NewImageBuffer

	size2 = CopyFileBufferToNewImageBuffer(pFileBuffer, size1, &pNewImageBuffer);
	if (size2 == 0 || !pNewImageBuffer)
	{
		printf("FileBuffer-->NewImageBuffer失败\r\n");
		free(pFileBuffer);
		return;
	}
	printf("FileBuffer-->NewImageBuffer成功\r\n");


	//NewImageBuffer -> 文件

	isOK = MemeryTOFile(pNewImageBuffer, size2, FilePath2);
	if (!isOK)
	{
		printf("新增节表和节存盘失败\r\n");
	}
	printf("新增节表和节存盘成功\r\n");

}

int main()
{
	NewSectionsInCodeSec();

	return 0;
}