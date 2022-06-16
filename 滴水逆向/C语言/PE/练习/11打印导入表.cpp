#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <windows.h>
#include <stdlib.h>

//char FILEPATH_IN[] = "D:/ipmsg.exe";
char FILEPATH_IN[] = "C:\\Windows\\System32\\notepad.exe";
char FILEPATH_OUT[] = "C:/copyxx.exe";


//1、File-> FileBuffer
//2、定位导入表
DWORD ReadPEFile(IN LPSTR lpszFile, OUT LPVOID* pFileBuffer)
{
	FILE* fp = NULL;
	DWORD fileSize = 0;
	LPVOID pBuffer = NULL;

	fp = fopen(lpszFile, "rb");
	if (!fp)
	{
		printf("lpszFile打开失败\n");
		return 0;
	}
	//获取文件大小
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//分配缓冲区
	pBuffer = malloc(fileSize);
	if (!pBuffer)
	{
		printf("pBuffer分配空间失败\n");
		fclose(fp);
		return 0;
	}

	//将文件数据读取到缓冲区
	size_t n = fread(pBuffer, fileSize,1, fp);
	if (!n)
	{
		printf("读取数据失败");
		free(pBuffer);		//释放内存
		fclose(fp);			//关闭文件
		return NULL;
	}


	*pFileBuffer = pBuffer;
	fclose(fp);
	pBuffer = NULL;
	return fileSize;

}


// RVA ->  FOA
DWORD RvaToFoa(DWORD dwRVA, LPVOID pFileBuffer)
{
	DWORD FOA = NULL;

	PIMAGE_DOS_HEADER pDos = NULL;
	PIMAGE_FILE_HEADER pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOP = NULL;
	PIMAGE_SECTION_HEADER  pSect = NULL;


	if (!pFileBuffer)
	{
		printf("pFileBuffer无效指针\n");
		return 0;
	}

	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	pPE = (PIMAGE_FILE_HEADER)((DWORD)pDos + pDos->e_lfanew + 4);
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);

	if (*(PWORD)pDos != IMAGE_DOS_SIGNATURE)
	{
		printf("不是有效MZ\n");
		return 0;
	}
	if (*(PDWORD)((DWORD)pDos + pDos->e_lfanew )!= IMAGE_NT_SIGNATURE)
	{
		printf("不是有效PE\n");
		return 0;
	}


	if (dwRVA <= pOP->SizeOfHeaders)
	{
		return dwRVA;
	}

	for (DWORD i = 0; i < pPE->NumberOfSections; i++)
	{
		if (dwRVA >= pSect->VirtualAddress && dwRVA <= pSect->VirtualAddress + pSect->Misc.VirtualSize)
		{
			FOA = dwRVA - pSect->VirtualAddress + pSect->PointerToRawData;
			return FOA;
		}
		pSect = (PIMAGE_SECTION_HEADER)((DWORD)pSect + IMAGE_SIZEOF_SECTION_HEADER);
	}
}



// FOA ->  RVA
DWORD FoaToRva(DWORD dwFOA, LPVOID pFileBuffer)
{
	DWORD RVA = NULL;
	PIMAGE_DOS_HEADER pDos = NULL;
	PIMAGE_FILE_HEADER pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOP = NULL;
	PIMAGE_SECTION_HEADER  pSect = NULL;


	if (!pFileBuffer)
	{
		printf("pFileBuffer无效指针\n");
		return 0;
	}

	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	pPE = (PIMAGE_FILE_HEADER)((DWORD)pDos + pDos->e_lfanew + 0x4);
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);

	if (*(PWORD)pDos != IMAGE_DOS_SIGNATURE)
	{
		printf("不是有效MZ\n");
		return 0;
	}
	if (*(PDWORD)((DWORD)pDos + pDos->e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		printf("不是有效PE\n");
		return 0;
	}

	if (dwFOA <= pOP->SizeOfHeaders)
	{
		return dwFOA;
	}

	for (DWORD i = 0; i < pPE->NumberOfSections; i++, pSect++)
	{
		if (dwFOA >= pSect->PointerToRawData && dwFOA <= pSect->PointerToRawData + pSect->SizeOfRawData)
		{
			RVA = dwFOA - pSect->PointerToRawData + pSect->VirtualAddress;
			return RVA;
		}
	}

}

//// 输出导入表
VOID PrintImport()
{
 
	DWORD Size = 0;
	LPVOID pFileBuffer = NULL;

	//FILE   ->  FileBuffer   //调用函数读取文件数据
	Size = ReadPEFile(FILEPATH_IN, &pFileBuffer);
	if (!pFileBuffer || !Size)
	{
			printf("File-> FileBuffer失败\n");
			return;
	}

	PIMAGE_DOS_HEADER  pDos = NULL;
	PIMAGE_FILE_HEADER  pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOP = NULL;
	PIMAGE_IMPORT_DESCRIPTOR  pImportDirectory = NULL; //导入表结构体

	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	pPE = (PIMAGE_FILE_HEADER)((DWORD)pDos + pDos->e_lfanew + 0x4);
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);

	DWORD ImportRVA = pOP->DataDirectory[1].VirtualAddress; //RVA
	DWORD ImportFOA = 0;

	//	判断导入表是否存在
	if (ImportRVA == 0)
	{
		printf("导入表不存在\n");
		return;
	}

	//导入表FOA
	ImportFOA = RvaToFoa(ImportRVA, pFileBuffer); 
	if (ImportRVA == 0)
	{
		printf("ImportFOA RVA -> FOA 失败\n");
		return;
	}

	//获取导入表地址
	pImportDirectory = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)pFileBuffer + ImportFOA);

	//循环打印每一个导入表的信息  重要成员为0时结束循环
	while (pImportDirectory->FirstThunk && pImportDirectory->OriginalFirstThunk)
	{
		//打印导入表文件名
		printf("=========================ImportTable %s Start=============================\n", \
			(PBYTE)((DWORD)pFileBuffer + RvaToFoa(pImportDirectory->Name, pFileBuffer)));
		//打印INT表RVA
		printf("OriginalFirstThunk RVA:%08X\n", pImportDirectory->OriginalFirstThunk);
		//获取INT表地址
		PDWORD pOriginalFirstThunk = (PDWORD)((DWORD)pFileBuffer + RvaToFoa(pImportDirectory->OriginalFirstThunk, pFileBuffer));
		printf("%x - %x\n", pOriginalFirstThunk, *pOriginalFirstThunk);//打印INT表的地址和序号

		while (*pOriginalFirstThunk)
		{
			//判读最高位是否为 1  
			if (*pOriginalFirstThunk & 0x80000000)
			{
				//高位为1 则 除去最高位的值就是函数的导出序号
				printf("按序号导入: %x\n",(*pOriginalFirstThunk)&0xFFF);
			}
			else
			{
				PIMAGE_IMPORT_BY_NAME pImageByName = (PIMAGE_IMPORT_BY_NAME)((DWORD)pFileBuffer + \
					RvaToFoa(*pOriginalFirstThunk, pFileBuffer));

				printf("按名字导入HIT/NAME: %x  -  %s\n", pImageByName->Hint, pImageByName->Name);
			}

			// 偏移 到 下一个
			pOriginalFirstThunk = (PDWORD)((DWORD)pOriginalFirstThunk + sizeof(IMAGE_THUNK_DATA32));
		}

		printf("**********************************************************************\n");

		printf("FirstThunk RVA: %08x\n", pImportDirectory->FirstThunk);
		PDWORD	pFirstThunk_FOA = (PDWORD)((DWORD)pFileBuffer + RvaToFoa(pImportDirectory->FirstThunk, pFileBuffer));
		printf("%x - %x\n", pFirstThunk_FOA, *pFirstThunk_FOA); //打印IAT表的地址和序号

		while (*pFirstThunk_FOA)
		{
			if (*pFirstThunk_FOA & 0x80000000)
			{
				printf("按序号导入: %x\n", (*pFirstThunk_FOA) & 0xFFF);
			}
			else
			{
				PIMAGE_IMPORT_BY_NAME pImageByName = (PIMAGE_IMPORT_BY_NAME)((DWORD)pFileBuffer + \
					RvaToFoa(*pFirstThunk_FOA, pFileBuffer));
				printf("按名字导入HIT/NAME: %x  -  %s\n", pImageByName->Hint, pImageByName->Name);
			}
			pFirstThunk_FOA = (PDWORD)((DWORD)pFirstThunk_FOA + sizeof(IMAGE_THUNK_DATA32)); //偏移到 下一个 
		}
		pImportDirectory++;
	}

	//释放内存
	free(pFileBuffer);
	return;
}

//**********************************************************************
int main(int argc, char* argv[])

{
	PrintImport();
	getchar();
	return 0;
}