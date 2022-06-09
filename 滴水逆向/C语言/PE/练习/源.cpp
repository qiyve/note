#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>


//��ȡ�ļ�
DWORD ReadPEFile(char* Filepath, LPVOID* pFileBuffer)
{
	LPVOID pTempBuffer = NULL;
	FILE* pf = NULL;
	DWORD Size = 0;

	//��ȡ�ļ�
	pf = fopen(Filepath, "rb");
	if (pf)
	{
		printf("�ļ���ȡʧ��\n");
		return 0;
	}
	fseek(pf, 0, SEEK_END);
	Size = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	pTempBuffer = malloc(Size);
	if (!pTempBuffer)
	{
		printf("����������ʧ��\n");
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
		printf("Rva_Foa pFileBuffer ��Чָ��\n");
		return 0;
	}
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)pDos) != IMAGE_DOS_SIGNATURE)
	{
		printf("����MZ���\n");
		return 0;
	}
	if (*((PDWORD)((DWORD)pDos + pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("����PE���\n");
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

	printf("��δ�ҵ�FOA\n");
	return 0;

}

//��ӡ������
void Printexport(LPVOID pFileBuffer)
{
	PIMAGE_DOS_HEADER			pDos = NULL;
	PIMAGE_OPTIONAL_HEADER32	 pOP = NULL;
	PIMAGE_EXPORT_DIRECTORY	 pExport = NULL;

	DWORD FoA;

	if (!pFileBuffer)
	{
		printf("Printexport pFileBuffer ��Чָ��\n");
		return;
	}
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)pDos) != IMAGE_DOS_SIGNATURE)
	{
		printf("����MZ���\n");
		return;
	}
	if (*((PDWORD)((DWORD)pDos + pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("����PE���\n");
		return;
	}

	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pDos + pDos->e_lfanew + 0x4 + IMAGE_SIZEOF_FILE_HEADER);

	//��ȡ�ļ��е�ַ  FOA
	FoA = Rva_Foa(pFileBuffer, pOP->DataDirectory->VirtualAddress);
	//�������ַ
	pExport = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pFileBuffer + FoA);

	printf("�����������%s\n", (DWORD)pFileBuffer + Rva_Foa(pFileBuffer, pExport->Name));
	printf("��������ʼ���%x\n", pExport->Base);
	printf("������������%x\n", pExport->NumberOfFunctions);
	printf("�����Ƶ����ĺ�������%x\n", pExport->NumberOfNames);
	printf("������ַ��%x\n", (DWORD)pFileBuffer + Rva_Foa(pFileBuffer, pExport->AddressOfFunctions));
	printf("�������Ʊ�%x\n", (DWORD)pFileBuffer + Rva_Foa(pFileBuffer, pExport->AddressOfNames));
	printf("������ű�%x\n", (DWORD)pFileBuffer + Rva_Foa(pFileBuffer, pExport->AddressOfNameOrdinals));
	printf("***********************************************\n");


}


int main()
{
	return 0;
}


