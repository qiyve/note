#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

DWORD ReadPEFile(IN LPSTR lpszFile, OUT LPVOID* pFileBuffer)
{
	// �����и�IN��OUT��������˼���ǲ��������ʹ������֮�󲻽��к���չ��
	//ɶҲ���ɣ���ʹ���ɸɣ�Ҳ����չ�ɿհף������C++�﷨������ģ�
	//LPSTR  ---->  typedef CHAR *LPSTR, *PSTR; ��˼����char* ָ�룻��WINNT.Hͷ�ļ�����
	// typedef unsigned long       DWORD;  DWORD���޷���4���ֽڵ�����
	//LPVOID ---->  typedef void far *LPVOID;��WINDEF.Hͷ�ļ����棻������voidָ������

	FILE* pFile = NULL;
	DWORD fileSize = 0;
	LPVOID pTempFileBuffer = NULL;

	//���ļ�
	pFile = fopen(lpszFile, "rb"); 
	if (!pFile)
	{
		printf("�����ļ�ʧ��\n");
		return 0;
	}

	/*
     ������ָ�������н����жϵĲ��������������ֵ�����ʹ�һ������������£�
     1.��Ϊָ���ж϶�Ҫ��NULL�Ƚϣ��൱��0����ֵ�����඼����ֵ
     2.if(!pFile)��if(pFile == NULL), ----> Ϊ�գ���ִ����䣻�������������ںŲ���һ�����ں�
     3.if(pFile)����if(pFile != NULL), ��Ϊ�գ���ִ����䣻
     */

	//��ȡ�ļ����ݺ󣬻�ȡ�ļ���С
	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	/*
	*  fseek ͨ��ʹ�ö����Ƶķ�ʽ���ļ����ƶ��ļ���дָ���λ��,��stdio.hͷ�ļ���
	int fseek(FILE * stream, long offset, int fromwhere);
	������fseek�ĺ���ԭ��
	��һ������stream Ϊ�ļ�ָ��
	�ڶ�������offset Ϊƫ������������ʾ����ƫ�ƣ�������ʾ����ƫ��
	����������fromwhere Ϊָ�����ʼλ��, �趨���ļ������￪ʼƫ��, ����ȡֵΪ��SEEK_CUR��SEEK_END��SEEK_SET
	SEEK_SET 0 �ļ���ͷ
	SEEK_CUR 1 ��ǰ��д��λ��
	SEEK_END 2 �ļ�β��*/

	//����ռ�
	pTempFileBuffer = malloc(fileSize);
	if (!pTempFileBuffer)
	{
		printf("�ڴ����ʧ��\n");
		fclose(pFile);
		return 0;
	}

	//�������뵽���ڴ�ռ䣬��ȡ����
	size_t n = fread(pTempFileBuffer, fileSize, 1, pFile);
	if (!n)
	{
		printf("��ȡ����ʧ��\n");
		free(pTempFileBuffer);  
		fclose(pFile);

		return 0;
    }

	//���ݶ�ȡ�ɹ����ر��ļ�
	*pFileBuffer = pTempFileBuffer;// ����ȡ�ɹ����������ڵ��ڴ�ռ���׵�ַ����ָ������pFileBuffer
	fclose(pFile);                 //�ر��ļ�

	return fileSize;               //���ػ�ȡ�ļ��Ĵ�С
}

//ͨ������FileBuffer������1000H���µ�ImageBuffer����
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

	//�ж϶�ȡpFileBuffer��ȡ�Ƿ�ɹ�
	if (!pFileBuffer)
	{
		printf("pFileBuffer������ָ����Ч\n");
		return 0;
	}

	//�ж��Ƿ�ΪMZ��־
	if ((*(PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE) // IMAGE_DOS_SIGNATURE --> MZ
	{
		printf("������ЧMZ���\n");
		return 0;
	}

	//�ж��Ƿ���PE���
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*(PWORD)((DWORD)pDos + pDos->e_lfanew) != IMAGE_NT_SIGNATURE) // IMAGE_NT_SIGNATURE --> PE
	{
		printf("������ЧPE���\n");
		return 0;
	}

	//*********************���뿪���ڴ�ռ�*****************************************************************

	sizeOfFile = fileSize + 0x1000;
	pTempNewImageBuffer = malloc(sizeOfFile);

	//�ж��ڴ�ռ��Ƿ񿪱ٳɹ�
	if (!pTempNewImageBuffer)
	{
		printf("pTempNewImageBuffer�����ڴ�ʧ��\n");
		return 0;
	}

	//��ʼ���ڴ�����
	memset(pTempNewImageBuffer, 0, sizeOfFile);

	//��λDos��ַ
	pDos = (PIMAGE_DOS_HEADER)(pTempNewImageBuffer);
	//NTͷ
	pNt = (PIMAGE_NT_HEADERS)((DWORD)pDos + pDos->e_lfanew);
	//PEͷ
	pPE = (PIMAGE_FILE_HEADER)(((DWORD)pNt) + 0x04);
	//��ѡPEͷ
	pOp = (PIMAGE_OPTIONAL_HEADER32)(((DWORD)pPE) + IMAGE_SIZEOF_FILE_HEADER); //IMAGE_SIZEOF_FILE_HEADER -> 20���ֽ�
	
   //��һ���ڱ��ַ
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOp + pPE->SizeOfOptionalHeader);

	//���һ���ڱ��ַ
	pLastSect = &pSect[pPE->NumberOfSections - 1];

	// �ж��Ƿ����㹻�Ŀռ����һ���ڱ�
		//�ж�������
		/*
		SizeOfHeader - (DOS + �������� + PE��� + ��׼PEͷ + ��ѡPEͷ + �Ѵ��ڽڱ�) >= 2���ڱ�Ĵ�С
		SizeOfHeader�ڿ�ѡPEͷ����
		 */

	okAddSections = (DWORD)(pOp->SizeOfHeaders - (pDos->e_lfanew + 0x04 + sizeof(PIMAGE_FILE_HEADER))
		+ pPE->SizeOfOptionalHeader + sizeof(PIMAGE_SECTION_HEADER) * pPE->NumberOfSections);

	if (okAddSections <= 2 * sizeof(PIMAGE_SECTION_HEADER))
	{
		printf("���exe�ļ�ͷ��ʣ��ռ䲻��\n");
		free(pTempNewImageBuffer);
		return 0;
	}

	//����û���⣬�Ϳ�ʼ�޸�������
	//*************************�޸�����*******************************************************************

	 //��ʼ���½ڱ���Ϣ
	PWORD pNumberOfSecton = &pPE->NumberOfSections;
	PDWORD pSizeOfImage = &pOp->SizeOfImage;
}