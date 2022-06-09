#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>


//读取文件
DWORD ReadPEFile(char* Filepath, LPVOID* pFileBuffer)
{
	LPVOID pTempBuffer = NULL;
	FILE* pf = NULL;
	DWORD Size = 0;

	//读取文件
	pf = fopen(Filepath, "rb");
	if (pf)
	{
		printf("文件读取失败\n");
		return 0;
	}
	fseek(pf, 0, SEEK_END);
	Size = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	pTempBuffer = malloc(Size);
	if (!pTempBuffer)
	{
		printf("缓冲区分配失败\n");
		fclose(pf);
		return 0;
	}

    memset(pTempBuffer, 0, Size);
    fread(pTempBuffer,1,Size,pf);

	*pFileBuffer = pTempBuffer;
	pTempBuffer = NULL;
	fclose(pf);

	return Size;
}

DWORD Rva_Foa(IN LPVOID pFileBuffer, DWORD Rva)
{
	PIMAGE_DOS_HEADER			 pDos= NULL;
	PIMAGE_FILE_HEADER			 pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32	 pOP = NULL;
	PIMAGE_SECTION_HEADER	   pSect = NULL;
	PIMAGE_SECTION_HEADER	   pTempSect = NULL;

	DWORD FoA = 0;

	if(!pFileBuffer)
	{ 
		printf("Rva_Foa pFileBuffer 无效指针\n");
		return 0;
	}
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)pDos) != IMAGE_DOS_SIGNATURE)
	{
		printf("不是MZ标记\n");
		return 0;
	}
	if (*((PDWORD)((DWORD)pDos + pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("不是PE标记\n");
		return 0;
	}
	pPE = (PIMAGE_FILE_HEADER)((DWORD)pDos + pDos->e_lfanew + 0x4);
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);

	pTempSect = pSect;

	if (Rva <= pOP->SizeOfHeaders)
	{
		printf("FoA:%x\n", Rva);
		return (DWORD)Rva;
	}
	for (int i = 0; i < pPE->NumberOfSections; i++, pTempSect)
	{
		if (Rva > pTempSect->VirtualAddress && Rva < pTempSect->VirtualAddress + pTempSect->Misc.VirtualSize)
		{
			FoA = Rva - pTempSect->VirtualAddress + pTempSect->PointerToRawData;

			printf("FoA = %x\n", Rva);
			return (DWORD)FoA;
		}
	}

	printf("并未找到FOA\n");
	return 0;

}

//打印导出表
void Printexport(LPVOID pFileBuffer)
{
	PIMAGE_DOS_HEADER			pDos = NULL;
	PIMAGE_OPTIONAL_HEADER32	 pOP = NULL;
	PIMAGE_EXPORT_DIRECTORY	 pExport = NULL;

	DWORD FoA;

	if (!pFileBuffer)
	{
		printf("Printexport pFileBuffer 无效指针\n");
		return;
	}
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)pDos) != IMAGE_DOS_SIGNATURE)
	{
		printf("不是MZ标记\n");
		return;
	}
	if (*((PDWORD)((DWORD)pDos + pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("不是PE标记\n");
		return;
	}

	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pDos + pDos->e_lfanew + 0x4 + IMAGE_SIZEOF_FILE_HEADER);

	//获取文件中地址  FOA
	FoA = Rva_Foa(pFileBuffer, pOP->DataDirectory->VirtualAddress);
	//导出表地址
	pExport = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pFileBuffer + FoA);

	printf("导出表的名字%s\n", (DWORD)pFileBuffer + Rva_Foa(pFileBuffer, pExport->Name));
	printf("导出表起始序号%x\n", pExport->Base);
	printf("导出表函数总数%x\n", pExport->NumberOfFunctions);
	printf("以名称导出的函数总数%x\n", pExport->NumberOfNames);
	printf("函数地址表%x\n", (DWORD)pFileBuffer + Rva_Foa(pFileBuffer, pExport->AddressOfFunctions));
	printf("函数名称表%x\n", (DWORD)pFileBuffer + Rva_Foa(pFileBuffer, pExport->AddressOfNames));
	printf("函数序号表%x\n", (DWORD)pFileBuffer + Rva_Foa(pFileBuffer, pExport->AddressOfNameOrdinals));
	printf("***********************************************\n");


}


int main()
{
	return 0;
}


