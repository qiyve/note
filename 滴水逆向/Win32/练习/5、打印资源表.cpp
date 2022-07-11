#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>

#define IN_PATH "ipmsg.exe"

DWORD ReadFileBuffer(LPSTR File_pata, LPVOID* pFilebuffer)
{
    FILE* pf = NULL;
    DWORD Size = 0;
    LPVOID pBuffer = NULL;

    pf = fopen(File_pata, "rb");
    if (!pf)
    {
        printf("文件读取失败!\n");
        return 0;
    }

    fseek(pf, 0, SEEK_END);
    Size = ftell(pf);
    fseek(pf, 0, SEEK_SET);
    pBuffer = malloc(Size);
    if (!pBuffer)
    {
        printf("内存分配失败\n");
        fclose(pf);
        return 0;
    }

    DWORD n = fread(pBuffer, Size, 1, pf);
    if (!n)
    {
        printf("文件读取失败\n");
        free(pBuffer);
        fclose(pf);
        return 0;

    }

    *pFilebuffer = pBuffer;
    pBuffer = NULL;
    fclose(pf);
    return Size;
}

DWORD RvaToFoa(LPVOID pFileBuff, DWORD dwRVA)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;

    if (!pFileBuff)
    {
        printf("(FoaToImageOffset)Can't open file!\n");
        return 0;
    }

    if (*((PWORD)pFileBuff) != IMAGE_DOS_SIGNATURE)
    {
        printf("(FoaToImageOffset)No MZ flag, not exe file!\n");
        return 0;
    }

    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuff;
    if (*((PDWORD)((DWORD)pFileBuff + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("(FoaToImageOffset)Not a valid PE flag!\n");
        return 0;
    }

    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuff + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 4); // 这里必须强制类型转换
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);
    PIMAGE_SECTION_HEADER pSectionTemp = pSectionHeader;

    if (dwRVA <= pOptionHeader->SizeOfHeaders)
    {
        return dwRVA;
    }

    for (DWORD i = 0; i < pPEHeader->NumberOfSections; i++, pSectionTemp++)
    {
        if (dwRVA >= pSectionTemp->VirtualAddress && dwRVA < pSectionTemp->VirtualAddress + pSectionTemp->Misc.VirtualSize)
        {
            return dwRVA - pSectionTemp->VirtualAddress + pSectionTemp->PointerToRawData;
        }
    }

    printf("未找到该值的FOA\n");
    return 0;
}


// 打印资源表
VOID PrintResourceTable(LPVOID pFileBuffer)
{
	//资源的类型
	PCHAR lpszResType[17] = { "未定义", "光标", "位图", "图标", "菜单",
		"对话框", "字符串","字体目录", "字体",
		"加速键", "非格式化资源", "消息列表", "光标组",
		"未定义", "图标组","未定义", "版本信息" };

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	PIMAGE_FILE_HEADER pPEHeader = (PIMAGE_FILE_HEADER)(pDosHeader->e_lfanew + (DWORD)pDosHeader + 4);
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + sizeof(IMAGE_FILE_HEADER));
	PIMAGE_SECTION_HEADER pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

	// 地位资源目录   第一层
	PIMAGE_RESOURCE_DIRECTORY pResDir1 = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)pFileBuffer + \
		RvaToFoa(pFileBuffer, pOptionHeader->DataDirectory[2].VirtualAddress)); // 获取文件中的偏移
	// 定位资源目录项  第一层
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDirEntry1 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResDir1 + \
		sizeof(IMAGE_RESOURCE_DIRECTORY));

	//获取第一层资源类型数量   资源类型数量 = NumberOfNamedEntries + NumberOfIdEntries
	int dwNumberOfResDirEntry1 = pResDir1->NumberOfNamedEntries + pResDir1->NumberOfIdEntries;
	//printf("资源类型数量: %d\n", dwNumberOfResDirEntry1);
	// 遍历第一层：类型
	for (int i = 0; i < dwNumberOfResDirEntry1; i++)
	{
		// 如果高位是1，低31位是指针，指向一个Unicode字符串
		if (pResDirEntry1[i].NameIsString == 1)
		{
			PIMAGE_RESOURCE_DIR_STRING_U uString =
				(PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)pResDir1 + (pResDirEntry1[i].NameOffset & 0x7FFFFFFF));

			//  2 * (uString->Length + 1)) 需要存储宽字符    uString->Length + 1 方便读取从堆中读取，宽字符以 0 0 结尾
			WCHAR* pName = (WCHAR*)malloc(2 * (uString->Length + 1));
			memset(pName, 0, 2 * (uString->Length + 1));
			memcpy(pName, uString->NameString, 2 * uString->Length);
			wprintf(L"ID:  - 资源类型: \"%s\"\n", pName);
			free(pName);
		}
		// 如果最高位是0，则这是一个序号，是预定义的16种资源之一
		else
		{
			if (pResDirEntry1[i].Id <= 16)
				printf("ID: %2d 资源类型: %s\n", pResDirEntry1[i].Id, lpszResType[pResDirEntry1[i].Id]);
			else
				printf("ID: %2d 资源类型: 未定义\n", pResDirEntry1[i].Id);
		}

		// 定义第二层的指针		资源目录
		PIMAGE_RESOURCE_DIRECTORY pResDir2 = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)pResDir1 + \
			(pResDirEntry1[i].OffsetToData & 0x7FFFFFFF));
		// 第二层  资源目录项
		PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDirEntry2 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResDir2 + \
			sizeof(IMAGE_RESOURCE_DIRECTORY));

		//第二层数据个数
		int dwNumberOfResDirEntry2 = pResDir2->NumberOfNamedEntries + pResDir2->NumberOfIdEntries;
		// 遍历第二层：编号
		//printf("第二层项数: %d\n", dwNumberOfNumber);		
		for (int j = 0; j < dwNumberOfResDirEntry2; j++)
		{
			if (pResDirEntry2[j].NameIsString == 1)
			{
				//低32位 是指向一个Unicode字符串 指针
				PIMAGE_RESOURCE_DIR_STRING_U uString =
					(PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)pResDir1 + (pResDirEntry2[j].NameOffset & 0x7FFFFFFF));
				WCHAR* pName = (WCHAR*)malloc(2 * (uString->Length + 1));
				memset(pName, 0, 2 * (uString->Length + 1));
				memcpy(pName, uString->NameString, 2 * uString->Length);
				wprintf(L"\tName: \"%s\"\n", pName);
				free(pName);
			}
			else
			{
				printf("\tID: %d\n", pResDirEntry2[j].Id);
			}
			// 定义第三层的指针和长度		
			PIMAGE_RESOURCE_DIRECTORY pResDir3 = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)pResDir1 + \
				(pResDirEntry2[j].OffsetToData & 0x7FFFFFFF));

			PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDirEntry3 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResDir3 + \
				sizeof(IMAGE_RESOURCE_DIRECTORY));

			int dwNumberOfResDirEntry3 = pResDir3->NumberOfNamedEntries + pResDir3->NumberOfIdEntries;
			// 遍历第三层：代码页
			// 大多数情况下一个资源的代码页只定义一种，但不是绝对，因此第三层也要循环遍历			
			//printf("\t\t%d\n", dwNumberOfResDirEntry3); // 真有不是1的
			for (int k = 0; k < dwNumberOfResDirEntry3; k++)
			{
				if (pResDirEntry3[k].Name & 0x80000000)
				{
					printf("\t非标准代码页\n");
				}
				else
				{
					printf("\t代码页: %d\n", pResDirEntry3[k].Id & 0x7FFF);
				}
				// 资源数据项，通过这个结构可以找到资源的RVA，以及大小
				PIMAGE_RESOURCE_DATA_ENTRY pDataEntry = (PIMAGE_RESOURCE_DATA_ENTRY)((DWORD)pResDir1 + \
					pResDirEntry3[k].OffsetToData);
				printf("\tRVA: %x\tSIZE: %x\n", pDataEntry->OffsetToData, pDataEntry->Size);
			}
			printf("\n");
		}
	}
}

int main()
{
    LPVOID pFileBuffer = NULL;

    ReadFileBuffer((LPSTR)IN_PATH, &pFileBuffer);
	PrintResourceTable(pFileBuffer);

	return 0;
}

