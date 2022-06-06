#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<malloc.h>

char file_path[] = "ipmsg.exe";
char save_path[] = "ipmsg_s.exe";

//最后一个节扩大0x1000
DWORD Fileread(char** Filebuffer) 
{
	FILE* fp = NULL;
	char* filebuffer = NULL;
	int file_size = 0;

	fp = fopen(file_path, "rb");
	if (!fp)
	{
		printf("文件读取失败\n");
		return 0;
	}
	//获取大小
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	filebuffer = (char*)malloc(file_size + 0x1000);
	if (!filebuffer)
	{
		printf("内存分配失败\n");
	}

	size_t n = fread(filebuffer, file_size, 1, fp);
	if (!n)
	{
		printf("读取数据失败!\r\n");
		free(filebuffer);   // 释放内存空间
		fclose(fp);      // 关闭文件流
		return 0;
	}

	fclose(fp);
	*Filebuffer = filebuffer;
	return file_size + 0x1000;
}

DWORD ExPand_Section(int x, char* filebuffer)
{
	PIMAGE_DOS_HEADER			pDosHeader	   = NULL;
	PIMAGE_NT_HEADERS			pNTHeader	   = NULL;
	PIMAGE_FILE_HEADER			pPEHeader	   = NULL;
	PIMAGE_OPTIONAL_HEADER32	pOptionHeader  = NULL;
	PIMAGE_SECTION_HEADER		pSectionHeader = NULL;

	pDosHeader = (PIMAGE_DOS_HEADER)filebuffer;
	//判断是否是有效指针
	if (!filebuffer)
	{
		printf("指针无效\n");
		return 0;
	}

	//判断mz标记
	if (*(PWORD)pDosHeader != IMAGE_DOS_SIGNATURE)
	{
		printf("不是有效MZ\n");
		return 0;
	}

	if (*((PDWORD)((DWORD)filebuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("不是有效的PE文件\n");
		return 0;
	}

	pNTHeader		= (PIMAGE_NT_HEADERS)((DWORD)filebuffer + pDosHeader->e_lfanew);
	pPEHeader		= (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 4);
	pOptionHeader	= (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
	pSectionHeader  = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

	//获取最后一个节表位置 
	PIMAGE_SECTION_HEADER endsectionheader = pSectionHeader + pPEHeader->NumberOfSections - 1;

	//修改 对齐前、后大小 为 + 0x1000
	endsectionheader->Misc.VirtualSize += 0x1000;
	endsectionheader->SizeOfRawData += 0x1000;
	pOptionHeader->SizeOfImage += 0x1000;

	//存盘
	FILE* fp = NULL;
	fp = fopen(save_path, "wb");
	fwrite(filebuffer, 1, x, fp);
	fclose(fp);

	return 0;
}
DWORD test() 
{

	char* filebuffer = NULL;
	int x = Fileread(&filebuffer);

	ExPand_Section(x, filebuffer);
	return 0;
}
int main() 
{
	test();

	return 0;
}
