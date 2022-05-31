#include"04PE加载过程.h"


DWORD ReadPEFile(IN LPSTR lpszFile, OUT LPVOID* pFileBuffer)
{
	FILE* pfile = NULL;
	DWORD FileSize = 0;
	LPVOID ptempBuffer = NULL;

	pfile = fopen(lpszFile, "rb");
	if (!pfile)
	{
		printf("exe打开失败！\n");
		return 0;
	}

	//读取文件大小
	fseek(pfile, 0, SEEK_END);
	FileSize = ftell(pfile);
	fseek(pfile, 0, SEEK_SET); 

	//开辟空间
	ptempBuffer = malloc(FileSize);
	if (!ptempBuffer)
	{
		printf("内存分配失败\n");
		fclose(pfile);
		return 0;
	}

	size_t n = fread(ptempBuffer, FileSize,1, pfile);
	if (!n)
	{
		printf("ReadPEFile文件读取失败\n");
		fclose(pfile);
		return 0;
	}
	printf("ReadPEFile文件读取成功\n");

	*pFileBuffer = ptempBuffer;
	ptempBuffer = NULL;
	fclose(pfile);

	return FileSize;

}

DWORD CopyFileBufferToImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID* pImageBuffer)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	PIMAGE_FILE_HEADER pFileHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptonalHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	// 临时指针
	LPVOID TempBuffer = NULL;

	if (pFileBuffer == NULL)
	{
		printf("pFileBuffer指针无效\n");
		return 0;
	}
	//判断是否是有效MZ标记
	pDosHeader = (PIMAGE_DOS_HEADER)(DWORD)pFileBuffer;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		printf("pFileBuffer不是有效MZ标记\n");
		return 0;
	}
	//判断PE标志
	if (*((PDWORD)((DWORD)pDosHeader + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("pFileBuffer不是有效PE标志\n");
		return 0;
	}

	pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + pDosHeader->e_lfanew);
	pFileHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNtHeader) + 4);
	//可选PE头
	pOptonalHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pFileHeader + IMAGE_SIZEOF_FILE_HEADER);
	//第一个节表指针
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptonalHeader + pFileHeader->SizeOfOptionalHeader);

	//根据SizeOflmage申请新空间
	TempBuffer = malloc(pOptonalHeader->SizeOfImage);
	if (!TempBuffer)
	{
		printf("TempBuffer内存分配失败");
		TempBuffer = NULL;
		return 0;
	}
	//初始化新的缓存区
	memset(TempBuffer, 0, pOptonalHeader->SizeOfImage);
	//拷贝所有头   SizeOfHeaders
	memcpy(TempBuffer, pDosHeader, pOptonalHeader->SizeOfHeaders); //参数1:目标容器  参数2:起始位置  参数3:结束位置
	//根据节表 循环cpy
	PIMAGE_SECTION_HEADER pTempSH = pSectionHeader;
	for (int i = 0; i < pFileHeader->NumberOfSections; i++, pTempSH++)
	{
		// 节区首地址    dos头 + PointerToRawDAta = 节区偏移地址      pTempSH->SizeOfRawData :文件对齐后的地址 则结束位置
		memcpy((void*)((DWORD)TempBuffer + pTempSH->VirtualAddress),
			(void*)((DWORD)pDosHeader + pTempSH->PointerToRawData), pTempSH->SizeOfRawData);
	}
	printf("CopyFileBufferToImageBuffer成功\n");

	//返回数据
	*pImageBuffer = TempBuffer;
	TempBuffer = NULL;

	return pOptonalHeader->SizeOfImage;
}

DWORD CopyImageBufferToNewBuffer(IN LPVOID pImageBuffer, OUT LPVOID* pNewBuffer)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	PIMAGE_FILE_HEADER pFileHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptonalHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;

	LPVOID Temp_NewBuffer = NULL;

	if (pImageBuffer == NULL)
	{
		printf("pImageBuffer指针无效\n");
		return 0;
	}
	//判断是否是有效MZ标记
	pDosHeader = (PIMAGE_DOS_HEADER)(DWORD)pImageBuffer;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		printf("不是有效MZ标记\n");
		return 0;
	}
	//判断PE标志
	if (*((PDWORD)((DWORD)pDosHeader + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("不是有效PE标志\n");
		return 0;
	}
	pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + pDosHeader->e_lfanew);
	pFileHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNtHeader) + 4);
	//可选PE头
	pOptonalHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pFileHeader + IMAGE_SIZEOF_FILE_HEADER);
	//第一个节表指针
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptonalHeader + pFileHeader->SizeOfOptionalHeader);
	//获取文件大小




	DWORD ImageBuff_Size = pOptonalHeader->SizeOfHeaders;
	//遍历节表
	for (size_t i = 0; i < pFileHeader->NumberOfSections; i++)
	{
		ImageBuff_Size += pSectionHeader[i].SizeOfRawData;
	}
	//开辟空间
	Temp_NewBuffer = malloc(ImageBuff_Size);
	if (!Temp_NewBuffer)
	{
		printf("Temp_NewBuffer分配失败 \n");
		Temp_NewBuffer = NULL;
		return 0;
	}

	//初始化全为0 
	memset(Temp_NewBuffer, 0, ImageBuff_Size);
	//拷贝头
	memcpy(Temp_NewBuffer, pDosHeader, pOptonalHeader->SizeOfHeaders);

	for (size_t i = 0; i < pFileHeader->NumberOfSections; i++ , pSectionHeader++)
	{
		memcpy((void*)((DWORD)Temp_NewBuffer + pSectionHeader->PointerToRawData),
			(void*)((DWORD)pImageBuffer + pSectionHeader->VirtualAddress),
			pSectionHeader->Misc.VirtualSize);
	}

	*pNewBuffer = Temp_NewBuffer;
	Temp_NewBuffer = NULL;

	printf("CopyImageBufferToNewBuffer成功\n");

	return ImageBuff_Size;

}


BOOL MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT LPSTR lpszFile)
{
	FILE* pf = NULL;
	pf = fopen(lpszFile, "wb");
	if (!pf)
	{
		printf("MemeryTOFile 文件读取失败\n");
		return 0;
	}

	fwrite(pMemBuffer, size, 1, pf);//向磁盘写入数据
	fclose(pf);
	pf = NULL;
	return 0;
}


DWORD RvaToFileOffset(IN LPVOID pFileBuffer, IN DWORD dwRva)
{

	return 0;
}
