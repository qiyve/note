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
//	//��ȡ�ļ�
//	pF = fopen(lpszFile, "rb");
//	if (!pF)
//	{
//		printf("�ļ���ȡʧ��\n");
//		return 0;
//	}
//	fseek(pF, 0, SEEK_END);
//	FileSize = ftell(pF);
//	fseek(pF, 0, SEEK_SET);
//
//	pTempBuffer = malloc(FileSize);
//	if (!pTempBuffer)
//	{
//		printf("�ڴ�ռ����ʧ��\n");
//		fclose(pF);
//		return 0;
//	}
//
//	size_t n = fread(pTempBuffer, FileSize,1, pF);
//	if (!n)
//	{
//		printf("��ȡ����ʧ��\n");
//		free(pTempBuffer);
//		fclose(pF);
//
//		return 0;
//	}
//	//���ݶ�ȡ�ɹ��� �ر��ļ�
//	*pFileBuffer = pTempBuffer;
//	pTempBuffer = NULL;
//	fclose(pF);
//	return FileSize;
//}
//
////�������һ���ڱ� 0x1000
//DWORD CopyFileBufferToNewImageBuffer(IN LPVOID pFileBuffer, IN size_t fileSize, OUT LPVOID* pNewImageBuffer)
//{
//	PIMAGE_DOS_HEADER			pDos = NULL;
//	PIMAGE_NT_HEADERS			pNT  = NULL;
//	PIMAGE_FILE_HEADER			pPE  = NULL;
//	PIMAGE_OPTIONAL_HEADER32	pOP  = NULL;
//	PIMAGE_SECTION_HEADER		pSect = NULL;
//	PIMAGE_SECTION_HEADER		endSect = NULL; //��¼���һ���ڱ�λ��
//
//	LPVOID pTmenNewBuffer = NULL;
//	DWORD FileSize = fileSize;   //��¼��С
//	DWORD size = 0x1000;  //��չ��С
//
//	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
//	pNT  = (PIMAGE_NT_HEADERS)((DWORD)pDos + pDos->e_lfanew);
//	pPE	 = (PIMAGE_FILE_HEADER)((DWORD)pNT + 0x4);
//	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
//	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);
//	endSect = pSect + pPE->NumberOfSections - 1;   // ���һ���ڱ�λ��
//
//
//
//	//�ж��Ƿ�����Чָ��
//	if (!pFileBuffer)
//	{
//		printf("ָ����Ч\n");
//		return 0;
//	}
//
//	//�ж�mz���
//	if (*(PWORD)pDos != IMAGE_DOS_SIGNATURE)
//	{
//		printf("������ЧMZ\n");
//		return 0;
//	}
//	//�ж�PE
//	if (*(PWORD)pNT != IMAGE_NT_SIGNATURE)
//	{
//		printf("������ЧPE\n");
//		return 0;
//	}
//
//	FileSize += size; //��ȡ��С
//	//���ٿռ�
//	pTmenNewBuffer = malloc(FileSize);
//	if (!pTmenNewBuffer)
//	{
//		printf("pTmenNewBuffer�ڴ����ʧ��\n");
//		pTmenNewBuffer = NULL;
//		return 0;
//	}
//
//	//�������һ���ڱ�
//	//��ʼ���ڴ�����
//	memset(pTmenNewBuffer, 0, FileSize);
//
//	//��ʼ�����֮���Ȱ�Ϊ�޸ĵ��ڴ�ռ�ȫ���������µ��ڴ�ռ�
//	memcpy(pTmenNewBuffer, pFileBuffer, fileSize);
// 
//	//�޸� �ڱ����ǰ�Ĵ�С
//	endSect->Misc.VirtualSize += size;
//	// ������С
//	endSect->SizeOfRawData += size;
//
//	//�޸�sizeofImage
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
//		printf("����ʧ��\n");
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
//		printf("���̳ɹ�\n");
//	}
//
//
//	return 0;
//}