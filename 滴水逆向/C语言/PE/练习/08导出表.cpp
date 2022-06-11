#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#define debug  0

//读取文件
DWORD ReadPEFile(char* Filepath, LPVOID* pFileBuffer)
{
	LPVOID pTempBuffer = NULL;
	FILE* pf = NULL;
	DWORD Size = 0;

	//读取文件
	pf = fopen(Filepath, "rb");
	if (!pf)
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


// dwRva 某个数据目录表 的virtualAddress 
DWORD RvaToOffset(IN LPVOID pFileBuffer, DWORD dwRva)
{
	PIMAGE_DOS_HEADER			 pDos= NULL;
	PIMAGE_FILE_HEADER			 pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32	 pOP = NULL;
	PIMAGE_SECTION_HEADER	   pSect = NULL;
	PIMAGE_SECTION_HEADER	   pTempSect = NULL;


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

	if (dwRva <= pOP->SizeOfHeaders)
	{
		printf("FoA:%x\n", dwRva);
		return dwRva;
	}
	for (int i = 0; i < pPE->NumberOfSections; i++, pTempSect++)
	{


		if (dwRva >= pTempSect->VirtualAddress && dwRva <= pTempSect->VirtualAddress + pTempSect->SizeOfRawData)
		{
			// dwRva - pTempSect->VirtualAddress   获得相对偏移
			// pTempSect->PointerToRawData  区段到buffer起始位置偏移
			
			printf("FoA = %x\n", dwRva);
			return  dwRva - pTempSect->VirtualAddress + pTempSect->PointerToRawData;
		}
	}

	return 0;
}



//打印导出表
void Printexport(LPVOID pFileBuffer)
{
	PIMAGE_DOS_HEADER		    pDos = NULL; 
	PIMAGE_NT_HEADERS		     pNT = NULL;
	PIMAGE_FILE_HEADER		     pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32     pOp = NULL;
	PIMAGE_SECTION_HEADER	   pSect = NULL;
	PIMAGE_DATA_DIRECTORY	   pData = NULL;  //存储导出表位置
	PIMAGE_EXPORT_DIRECTORY	 pExport = NULL;  //导出表首地址

	DWORD		 Foa = 0;

	if (pFileBuffer == NULL)
	{
		printf("FileBuffer 获取失败!\r\n");
		return;
	}

	//判断是否是有效的MZ标志
	if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
	{
		printf("无效的MZ标识\r\n");
		return;
	}
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;

	//判断是否是有效的PE标志
	if (*((PDWORD)((DWORD)pFileBuffer + pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("无效的PE标记\r\n");
		return;
	}
	//定位NT头
	pNT = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDos->e_lfanew);
	pPE = (PIMAGE_FILE_HEADER)(((DWORD)pNT) + 4);
	pOp = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);

	//	pData = PIMAGE_DATA_DIRECTORY((&pOptionHeader->NumberOfRvaAndSizes + 1));
	pData = pOp->DataDirectory;
	Foa = RvaToOffset(pFileBuffer, pData->VirtualAddress);
	printf("FoaAddress: %#X \r\n", Foa);
	pExport = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pDos + Foa);

	printf("\t\t RVA\t\t 大小\r\n");

	//打印相关信息测试
	//#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16

	//下面是一种粗糙的遍历写法；
	/*
	for (int i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++,pDataDirectory++)
	{
		printf("%#08X \r\n",pDataDirectory->VirtualAddress);
		printf("%#08X \r\n",pDataDirectory->Size);
	}
	*/

	//显示每个项目的位置 大小
	for (DWORD i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
	{
		//DirectoryString(i);
		printf("%08X\t%08X\r\n", pData[i].VirtualAddress, pData[i].Size);
	}

	printf("***********************************************************\r\n");
	printf("导出函数地址表(RVA)	: \t\t%#08X \r\n", pExport->AddressOfFunctions);
	printf("导出函数名称表(RVA) : \t\t%#08X \r\n", pExport->AddressOfNames);
	printf("导出函数序号表(RVA) : \t%#08X \r\n", pExport->AddressOfNameOrdinals);
	printf("导出函数起始序号 : \t\t\t%#08X \r\n", pExport->Base);
	printf("pExportDirectory->Characteristics : \t\t%#08X \r\n", pExport->Characteristics);
	printf("pExportDirectory->MajorVersion : \t\t%#08X \r\n", pExport->MajorVersion);
	printf("pExportDirectory->MinorVersion : \t\t%#08X \r\n", pExport->MinorVersion);
	printf("指向该导出表文件文件名字符串 : \t\t\t%#08X \r\n", pExport->Name);
	printf("所有导出函数的个数 : \t\t%#08X \r\n", pExport->NumberOfFunctions);
	printf("以函数名字导出的函数个数 : \t\t%#08X \r\n", pExport->NumberOfNames);
	printf("***********************************************************\r\n");


	//定义导出表函数地址，函数序号，导出表地址序号，函数名称对应文件中的FOA位置；
	//Name, AddressOfNames, AddressOfFunctions, AddressOfOrdinals;
	DWORD NameFoa = RvaToOffset(pFileBuffer, pExport->Name);
	DWORD AddressOfNamesFoa = RvaToOffset(pFileBuffer, pExport->AddressOfNames);
	DWORD AddressOfFunctionsFoa = RvaToOffset(pFileBuffer, pExport->AddressOfFunctions);
	DWORD AddressOfOrdinalsFoa = RvaToOffset(pFileBuffer, pExport->AddressOfNameOrdinals);

	//获取导出表名称，函数地址表，函数序号表，函数名称表；
	PBYTE pDllOrExeName = (PBYTE)((DWORD)pDos + NameFoa);
	//上面之所以使用PBYTE是因为要打印每个字符，需要一个一个字节读取；
	printf("导出表的名称: %s \r\n", pDllOrExeName);//这里打印出来的就是exe的名称ipmsg.exe

	//导出函数地址表，在文件中的位置
	PDWORD pAddressFunctionTable = (PDWORD)((DWORD)pDos + AddressOfFunctionsFoa);
	printf("函数地址表的位置: %#08X \r\n", pAddressFunctionTable);

	//导出函数序号表，在文件中的位置
	PDWORD pOrdinaFunctionTable = (PDWORD)((DWORD)pDos + AddressOfOrdinalsFoa);
	printf("函数序号表的位置: %#08X \r\n", pOrdinaFunctionTable);

	//导出函数名称表，在文件中的位置
	PDWORD pNameFunctionTable = (PDWORD)((DWORD)pDos + AddressOfNamesFoa);
	printf("函数名称表的位置: %#08X \r\n", pNameFunctionTable);


	//判断是以序号导出函数，还是以函数名字导出
	BOOL indexNumIsExist = FALSE;
	/*indexNumIsExist --> 简单点理解，这个参数就是要获得导出表函数名称下标和序号表下标她们之间如果能找到对应
	相同的下标，那么这个参数indexNumIsExist是TRUE，否则是FAlSE；

	详细解释：可以根据导出表函数名称下标号，对应序号表中的下标号，她们之间进行比对，
	如果在序号表和导出表函数名称表里面能够找到对应相同的下表号码，那么就可以根据在序号表中找到的下标号
	对应的值，拿着这个对应的值，就可以在导出表函数地址的这张表中去寻找下标为这个对应的值，然后就是对应
	导出表函数的地址；
	*/
	for (DWORD n = 0; n < pExport->NumberOfFunctions; n++)
		//n 是导出表函数地址表对应的下标，根据NumberOfFunctions的个数决定
	{
		//获取导出表函数地址表的起始位置;
		//printf("导出表函数地址表的位置: %#08X ",pAddressFunctionTable[n]);

		indexNumIsExist = FALSE;//这个参数为FALSE就表示，可以直接通过序号导出函数找函数地址
		//nNameIndex --> 导出表函数名称下标，这个下面是根据NumberOfNames个数决定，下面开始判断验证是否可以；
		DWORD nNameIndex;
		for (nNameIndex = 0; nNameIndex < pExport->NumberOfNames; nNameIndex++)
		{
			/*根据导出表函数名称的下标(索引)，这里理解就是直接将函数名称下标号当作序号表的下标，然后通过序号表
			 的起始位置加上这个序号表的下标去定位得出序号表中对应的值，是否等于导出表函数地址表的下标，而这个
			下标就是上面我们定义好的参数n，是导出表函数地址的个数，即下标号，如果相等，那么indexNumIsExist
			等于TRUE，得出结论可以通过函数名称导出函数；
			*/
			if (n == pOrdinaFunctionTable[nNameIndex])
			{
				indexNumIsExist = TRUE;
				break;
			}
		}

		if (indexNumIsExist == TRUE)
		{
			//下面是取出导出表函数名称表中对应下标的地址
			DWORD dwNameFoa = pNameFunctionTable[nNameIndex];//这里还是Rva地址
			PBYTE pFunctionName = (PBYTE)((DWORD)pDos + RvaToOffset(pFileBuffer, dwNameFoa));

			//上面是将导出表函数名称表对应下标的地址取出来对应的RVA地址，然后将其转换为FOA地址
			//再通过这个FOA的地址进行偏移，这个偏移就相当于是通过导出表函数名称表里面的地址，定位
			//到准确的函数名称，获取函数名称的字符串；

			printf("导出表函数名称-->[%s]", pFunctionName);
			printf("导出表函数地址表的位置: %#08X", pAddressFunctionTable[n]);
			//获取导出表函数序列号表
			printf("导出表函数序列号表: [%d] \r\n", n - pExport->Base);
			//序号表里面的值+Base的值=导出表函数地址表里面的下标值；
			//上面n是导出表函数地址表的下标值，所以n - pExportDirectory->Base就可以得到序号表的值
		}
		else
		{
			//如果上述不成立，序号表根本就不存在，判断是否存在这个函数
			if (pAddressFunctionTable[n] != 0)
			{
				//确认为是隐藏函数
				printf("导出表函数名称-->");
				printf("导出表函数地址表下标[%d]-->", n + pExport->Base);
				printf("导出表函数地址表的位置:%#08X ", pAddressFunctionTable[n]);
			}
		}
		printf("\r\n");
	}
	return;
}


//	2、GetFunctionAddrByName(FileBuffer指针，函数名指针)
DWORD	GetFunctionAddrByName(LPVOID pFileBuffer, LPSTR Name)
{
	printf("Function Name: %s\n", Name);

	PIMAGE_DOS_HEADER		 pDos = NULL;;
	PIMAGE_OPTIONAL_HEADER32  pOP = NULL;
	PIMAGE_DATA_DIRECTORY   pData = NULL;	   //存储导出表的偏移位置 和大小
	PIMAGE_EXPORT_DIRECTORY  pExport = NULL;   //导出表的首地址


	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pDos + pDos->e_lfanew + 0x4 + IMAGE_SIZEOF_FILE_HEADER);

	if (!pFileBuffer)
	{
		printf("FileBuffer 获取失败!\r\n");
		return NULL;
	}

	//判断是否是有效的MZ标志
	if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
	{
		printf("无效的MZ标识\r\n");
		return NULL;;
	}

	//判断是否是有效的PE标志
	if (*((PDWORD)((DWORD)pFileBuffer + pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("无效的PE标记\r\n");
		return NULL;;
	}

	//获取 导出表位置
	pData = (PIMAGE_DATA_DIRECTORY)pOP->DataDirectory;
	if (!pData->VirtualAddress)
	{
		printf("这个程序没有导出表.\n");
		return NULL;
	}

	printf("导出表 RVA:%x\n", pData->VirtualAddress);
	DWORD pExport_FOA = RvaToOffset(pFileBuffer, pData->VirtualAddress);
	printf("导出表 FOA:%x\n", pExport_FOA);

	pExport = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pOP + pExport_FOA);
	//上面操作完成之后，就是通过RVA转换为FOA地址，定位到了导出表的起始位置；

	if (!debug)
	{
		printf("Characteristics: %#X\r\n", pExport->Characteristics);
		printf("TimeDateStamp: %#X\r\n", pExport->TimeDateStamp);
		printf("MajorVersion: %#X\r\n", pExport->MajorVersion);
		printf("MinorVersion: %#X\r\n", pExport->MinorVersion);
		printf("Name: %s\r\n", (PVOID)((DWORD)pFileBuffer + RvaToOffset(pFileBuffer, pExport->Name)));
		printf("Base: %#X\r\n", pExport->Base);
		printf("NumberOfFunctions: %#X\r\n", pExport->NumberOfFunctions);
		printf("NumberOfNames: %#X\r\n", pExport->NumberOfNames);
		printf("AddressOfFunctions: %#X\r\n", pExport->AddressOfFunctions);
		printf("AddressOfNames: %#X\r\n", pExport->AddressOfNames);
		printf("AddressOfNameOrdinals: %#X\r\n", pExport->AddressOfNameOrdinals);
	}

	//同样是将导出表函数名称表，序号表，函数地址表对应起始位置的RVA转换为FOA
	DWORD Foa_AddressOfNames = RvaToOffset(pFileBuffer, pExport->AddressOfNames);
	DWORD Foa_AddressOfFunctions = RvaToOffset(pFileBuffer, pExport->AddressOfFunctions);
	DWORD Foa_AddressOfNameOrdinals = RvaToOffset(pFileBuffer, pExport->AddressOfNameOrdinals);

	if (!debug)
	{
		DWORD Foa_Address_Names = (DWORD)pFileBuffer + Foa_AddressOfNames;
		printf("AddressOfNames Offset Value: %#X\r\n", Foa_Address_Names);//偏移看看有没有内容
		printf("Foa_AddressOfNames: %#X\r\n", Foa_AddressOfNames);//看看转换后的地址
		printf("Foa_AddressOfNameOrdinals: %#X\r\n", Foa_AddressOfNameOrdinals);
		printf("Foa_AddressOfFunctions: %#X\r\n", Foa_AddressOfFunctions);
	}

	//1.通过循环确认从导出表函数名称表中找与目标函数名是否相同；如相同，则返回该名字在表中的索引
	DWORD ordIndex = -1;
	for (DWORD i = 0; i < pExport->NumberOfNames; i++)
	{
		DWORD nameOffset = *(PDWORD)((DWORD)pFileBuffer + (DWORD)((LPDWORD)Foa_AddressOfNames + i));
		/*上面得到的nameOffset的参数值的理解：
		Foa_AddressOfNames的值是0X5223C，这个是FileBuffer下对应的FOA内存偏移地址，通过FileBuffer
		直接移动到名称地址表(AddressOfNames)的首地址位置;这里有一个重点理解对象，就是我们看到的这些
		AddressOfNames，AddressOfNameOrdinals，AddressOfFunctions全是RVA地址，然后转换之后的FOA地址
		都是对应理解为像使用Winhex以16进制形式打开ipmsg.exe文件，然后最左边显示的那一对内存地址；
		就是我们所说的RVA地址和FOA地址，理解这个，就不难理解上面代码(LPDWORD)Foa_AddressOfNames + i)；
		她们自己相加实际是以使用Winhex以16进制形式打开ipmsg.exe文件的左边内存地址进行偏移依次找到对应
		名称地址表AddressOfNames的每个偏移地址，然后使用指针的方式通过* 取出里面对应的每个值，而这每个
		值也是RVA地址，所以得到的nameOffset的值需要再次转换为FOA地址，再使用文件FileBuffer偏移的方式
		找到真正的函数名称地址;
		*/

		LPSTR nameAddr = (LPSTR)((DWORD)pFileBuffer + RvaToOffset(pFileBuffer, nameOffset));
		if (!strcmp(nameAddr, Name))
		{
			ordIndex = i;
			break;
		}
	}

	if (ordIndex == -1)
	{
		printf("导出表中没有该函数名称\n");
		return 0;
	}
	//2.通过获得的索引在导出表序号表中找到对应函数的序号
	WORD ord = *(PWORD)((DWORD)pFileBuffer + (DWORD)((LPWORD)Foa_AddressOfNameOrdinals + ordIndex));
	if (!debug)
	{
		DWORD Foa_AddressNameOrdinals = (DWORD)pFileBuffer + Foa_AddressOfNameOrdinals;
		printf("AddressOfNameOrdinals Offset Value: %#X\r\n", Foa_AddressNameOrdinals);
		printf("Foa_AddressOfNameOrdinals: %#X\r\n", Foa_AddressOfNameOrdinals);
		printf("ordInex in AddressOfNames: %#X\r\n", ordIndex);
		printf("ordInex in AddressOfNameOrdinals: %#X\r\n", ord);
	}

	//3.通过序号表中查出来的值，当作下标索引从导出表函数地址表中找函数地址
	DWORD addr = *(PDWORD)((DWORD)pFileBuffer + (DWORD)((LPDWORD)Foa_AddressOfFunctions + ord));
	//DWORD Foa_AddrFun = RvaToFileOffset(pFileBuffer, addr);

	return addr;
}

//根据序号获取导出表函数地址
DWORD GetFunctionAddrByOrdinals(PVOID pFileBuffer, DWORD pFunctionOfOrdinal)
{
	printf("Function Ordinal: %#x\n", pFunctionOfOrdinal);
	// 初始化PE头部结构体
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	PIMAGE_DATA_DIRECTORY pDataDirectory = NULL;     //导出表的偏移 RVA 需转换FOA
	PIMAGE_EXPORT_DIRECTORY pExportDirectory = NULL;

	// 判断指针是否有效
	if (!pFileBuffer)
	{
		printf("pFileBuffer不是有效的指针\r\n");
		return 0;
	}
	//判断是否是有效的MZ标志
	if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
	{
		printf("pFileBuffer不是有效的MZ文件\r\n");
		return 0;
	}
	//判断是否是一个有效的PE标志
	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("pFileBuffer不是一个有效的PE标志\r\n");
		return 0;
	}

	// 强制结构体类型转换
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
	pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x04); // 这里必须强制类型转换
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);
	pDataDirectory = (PIMAGE_DATA_DIRECTORY)pOptionHeader->DataDirectory;


	if (!pDataDirectory->VirtualAddress)
	{
		printf("这个程序没有导出表.\r\n");
		return 0;
	}

	printf("导出表RVA地址: %#X\r\n", pDataDirectory->VirtualAddress);
	DWORD Foa_ExportTable = RvaToOffset(pFileBuffer, pDataDirectory->VirtualAddress);
	printf("导出表FOA地址: %#X\r\n", Foa_ExportTable);
	pExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pFileBuffer + Foa_ExportTable);

	if (!debug)
	{
		printf("Characteristics: %#X\r\n", pExportDirectory->Characteristics);
		printf("TimeDateStamp:%#X\r\n", pExportDirectory->TimeDateStamp);
		printf("MajorVersion: %#X\r\n", pExportDirectory->MajorVersion);
		printf("MinorVersion: %#X\r\n", pExportDirectory->MinorVersion);
		printf("Name: %s\r\n", (PVOID)((DWORD)pFileBuffer + RvaToOffset(pFileBuffer, pExportDirectory->Name)));
		printf("Base: %#X\r\n", pExportDirectory->Base);
		printf("NumberOfFunctions: %#X\r\n", pExportDirectory->NumberOfFunctions);
		printf("NumberOfNames: %#X\r\n", pExportDirectory->NumberOfNames);
		printf("AddressOfFunctions: %#X\r\n", pExportDirectory->AddressOfFunctions);
		printf("AddressOfNames: %#X\r\n", pExportDirectory->AddressOfNames);
		printf("AddressOfNameOrdinals: %#X\r\n", pExportDirectory->AddressOfNameOrdinals);
	}

	//下面就是算法来，如果是通过序号直接得出导出表函数地址表中的地址，那么只要序号-Base值即可
	DWORD Sequence = pFunctionOfOrdinal - pExportDirectory->Base;
	DWORD Foa_AddressOfFunctions = RvaToOffset(pFileBuffer, pExportDirectory->AddressOfFunctions);

	if (!debug)
	{
		DWORD Foa_AddressFunctions = Foa_AddressOfFunctions + (DWORD)pFileBuffer;
		printf("AddressOfFunctions里面内容: %#X\r\n", Foa_AddressFunctions);
		printf("Foa_AddressOfFunctions: %#X\r\n", Foa_AddressOfFunctions);
	}

	PDWORD pFoa_AddressOfFunctions = (PDWORD)((DWORD)pFileBuffer + Foa_AddressOfFunctions);
	for (DWORD n = 0; n < Sequence; n++)
	{
		pFoa_AddressOfFunctions++;
	}
	//DWORD Foa_AddrFun = RvaToFileOffset(pFileBuffer, *pFoa_AddressOfFunctions);
	return *pFoa_AddressOfFunctions;
}

}

int main()
{
	LPVOID FileBuffer = NULL;
	char path[] = "D:/ipmsg.exe";
	//LPSTR Name = "";

	ReadPEFile( path, &FileBuffer );
	//Printexport(FileBuffer);
	//GetFunctionAddrByName(FileBuffer,Name);
	//GetFunctionAddrByOrdinals(FileBuffer, 2);

	system("pause");
	return 0;
}



