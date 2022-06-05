//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<Windows.h>
//
//
//DWORD ReadPEFile(IN LPSTR lpszFile, OUT LPVOID* pFileBuffer)
//{
//	FILE* pF = NULL;
//	DWORD FileSize = 0;
//	LPVOID  pTempBuffer = NULL;
//
//	//读取文件
//	pF = fopen(lpszFile, "rb");
//	if (!pF)
//	{
//		printf("文件读取失败\n");
//		return 0;
//	}
//	fseek(pF, 0, SEEK_END);
//	FileSize = ftell(pF);
//	fseek(pF, 0, SEEK_SET);
//
//	pTempBuffer = malloc(FileSize);
//	if (!pTempBuffer)
//	{
//		printf("内存空间分配失败\n");
//		fclose(pF);
//		return 0;
//	}
//
//	size_t n = fread(pTempBuffer, FileSize,1, pF);
//	if (!n)
//	{
//		printf("读取数据失败\n");
//		free(pTempBuffer);
//		fclose(pF);
//
//		return 0;
//	}
//	//数据读取成功， 关闭文件
//	*pFileBuffer = pTempBuffer;
//	pTempBuffer = NULL;
//	fclose(pF);
//	return FileSize;
//}
//
////扩大最后一个节表 0x1000
//DWORD CopyFileBufferToNewImageBuffer(IN LPVOID pFileBuffer, IN size_t fileSize, OUT LPVOID* pNewImageBuffer)
//{
//	PIMAGE_DOS_HEADER			pDos = NULL;
//	PIMAGE_NT_HEADERS			pNT  = NULL;
//	PIMAGE_FILE_HEADER			pPE  = NULL;
//	PIMAGE_OPTIONAL_HEADER32	pOP  = NULL;
//	PIMAGE_SECTION_HEADER		pSect = NULL;
//	PIMAGE_SECTION_HEADER		endSect = NULL; //记录最后一个节表位置
//
//	LPVOID pTmenNewBuffer = NULL;
//	DWORD FileSize = fileSize;   //记录大小
//	DWORD size = 0x1000;  //扩展大小
//
//	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
//	pNT  = (PIMAGE_NT_HEADERS)((DWORD)pDos + pDos->e_lfanew);
//	pPE	 = (PIMAGE_FILE_HEADER)((DWORD)pNT + 0x4);
//	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
//	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);
//	endSect = pSect + pPE->NumberOfSections - 1;   // 最后一个节表位置
//
//
//
//	//判断是否是有效指针
//	if (!pFileBuffer)
//	{
//		printf("指针无效\n");
//		return 0;
//	}
//
//	//判断mz标记
//	if (*(PWORD)pDos != IMAGE_DOS_SIGNATURE)
//	{
//		printf("不是有效MZ\n");
//		return 0;
//	}
//	//判断PE
//	if (*(PWORD)pNT != IMAGE_NT_SIGNATURE)
//	{
//		printf("不是有效PE\n");
//		return 0;
//	}
//
//	FileSize += size; //获取大小
//	//开辟空间
//	pTmenNewBuffer = malloc(FileSize);
//	if (!pTmenNewBuffer)
//	{
//		printf("pTmenNewBuffer内存分配失败\n");
//		pTmenNewBuffer = NULL;
//		return 0;
//	}
//
//	//扩大最后一个节表
//	//初始化内存内容
//	memset(pTmenNewBuffer, 0, FileSize);
//
//	//初始化完成之后，先把为修改的内存空间全部拷贝到新的内存空间
//	memcpy(pTmenNewBuffer, pFileBuffer, fileSize);
// 
//	//修改 节表对齐前的大小
//	endSect->Misc.VirtualSize += size;
//	// 对齐后大小
//	endSect->SizeOfRawData += size;
//
//	//修改sizeofImage
//	pOP->SizeOfImage += size;
//
//	*pNewImageBuffer = pTmenNewBuffer;
//	pTmenNewBuffer = NULL;
//
//
//	return pOP->SizeOfImage;
//}
//
//BOOL MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT LPSTR lpszFile)
//{
//	FILE* pF = NULL;
//	pF = fopen(lpszFile, "wb+");
//	if (!pF)
//	{
//		printf("存盘失败\n");
//		fclose(pF);
//		return FALSE;
//	}
//
//	fwrite(pMemBuffer, size, 1, pF);
//	fclose(pF);
//	pF = NULL;
//	return TRUE;
//}
//
//
//int main()
//{
//	char file_IN[] = "D:/ipmsg.exe";
//	char file_OUT[] = "ipmsg_s.exe";
//
//	LPVOID pFileBuffer = NULL;
//	LPVOID pImageBuffer = NULL;
//
//	DWORD size1 = 0;
//	DWORD size2 = 0;
//	DWORD isOK = 0;
//
//
//
//	size1 = ReadPEFile(file_IN, &pFileBuffer);
//	size2 = CopyFileBufferToNewImageBuffer(pFileBuffer, size1, &pImageBuffer);
//	isOK = MemeryTOFile(pImageBuffer, size2, file_OUT);
//	if (isOK)
//	{
//		printf("存盘成功\n");
//	}
//
//
//	return 0;
//}