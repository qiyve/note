#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>

#define FilePath_In "C:\\Windows\\System32\\notepad.exe"
#define debug  0   //调试

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
	fread(pTempBuffer, 1, Size, pf);

	*pFileBuffer = pTempBuffer;
	pTempBuffer = NULL;
	fclose(pf);

	return Size;
}


DWORD RvaToOffset(IN LPVOID pFileBuffer, DWORD dwRva)
{
	PIMAGE_DOS_HEADER pDos = NULL;
	PIMAGE_NT_HEADERS pNT = NULL;
	PIMAGE_FILE_HEADER pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOP = NULL;
	PIMAGE_SECTION_HEADER pSect = NULL;
	
	DWORD NumberOfSection = 0;
	DWORD dwFOA = 0;

	//判断指针是否有效
	if (!pFileBuffer)
	{
		printf("pFileBuffer指针无效\n");
		return 0;
	}

	//判断MZ标记
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)pDos) != IMAGE_DOS_SIGNATURE)
	{
		printf("不是有效MZ标记\n");
		return 0;
	}

	//判断PE
	pNT = (PIMAGE_NT_HEADERS)((DWORD)pDos + pDos->e_lfanew);
	if (*((PDWORD)pNT) != IMAGE_NT_SIGNATURE)
	{
		printf("不是有效PE标记\n");
		return 0;
	}

	pPE = (PIMAGE_FILE_HEADER)((DWORD)pNT + 0x4);
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);

	//定义个临时节表指针进行下面的计算操作
	NumberOfSection = pPE->NumberOfSections;
	PIMAGE_SECTION_HEADER pTempSect = pSect;

	//判断dwRva所在的节
	if (dwRva <= pOP->SizeOfHeaders)
	{
		return (DWORD)dwRva;
	}
		//上面是判断如果rva地址所处的节在第一个节之前那么直接返回rva的地址；
		//否则下面就是开始遍历查找节；
	else
	{
		for (DWORD i = 0; i < NumberOfSection; i++, pTempSect++)
		{
			if ((dwRva >= pTempSect->VirtualAddress) && (dwRva <= pTempSect->VirtualAddress + pTempSect->Misc.VirtualSize))
			{
				dwFOA = dwRva - pTempSect->VirtualAddress + pTempSect->PointerToRawData;
			}
		}
	}
	return dwFOA;
}

 //输出重定位表
DWORD GetDataDirectoyOfBaseRelocation(IN PVOID pFileBuffer)
{
	// 初始化PE头部结构体
	PIMAGE_DOS_HEADER  pDos = NULL;
	PIMAGE_NT_HEADERS  pNT = NULL;
	PIMAGE_FILE_HEADER pPE = NULL;
	PIMAGE_OPTIONAL_HEADER32  pOP = NULL;
	PIMAGE_SECTION_HEADER   pSect = NULL;

	PIMAGE_DATA_DIRECTORY   pDataDirectory = NULL;   //目录项目数  首地址
	PIMAGE_BASE_RELOCATION  pBaseRelocation = NULL;  //重定位表   首地址

	DWORD RVA_BaseRelocationTable = 0;            //重定位表的位置  RVA
	DWORD SizeOfBlock_BaseRelocationTable = 0;    // 块的大小

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
	pDos = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)((DWORD)pFileBuffer + pDos->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("pFileBuffer不是一个有效的PE标志\r\n");
		return 0;
	}

	// 强制结构体类型转换
	pNT = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDos->e_lfanew);
	pPE = (PIMAGE_FILE_HEADER)((DWORD)pNT + 0x04); // 这里必须强制类型转换
	pOP = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPE + IMAGE_SIZEOF_FILE_HEADER);
	pSect = (PIMAGE_SECTION_HEADER)((DWORD)pOP + pPE->SizeOfOptionalHeader);
	//pSectionHeader = (PIMAGE_SECTION_HEADER)(pNTHeader+0x01);
	//上述表示节表指针pSectionHeader的另一种写法，就是通过NT头的这个一个整体的结构体宽度进行移动；
	//因为NT头整体结构体宽度是4+20+224=248 --> 16进制F8，通过加0x01就直接移动F8的字节，刚好落在节表位置；

	pDataDirectory = (PIMAGE_DATA_DIRECTORY)pOP->DataDirectory;

	//定位重定位表VirtualAddress 即RVA地址  | 宏 IMAGE_DIRECTORY_ENTRY_BASERELOC  [5]  |    数据目录项的第6个结构，就是重定位表.
	RVA_BaseRelocationTable = pDataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
	//定位重定位表SizeOfBlock,即 块的大小
	SizeOfBlock_BaseRelocationTable = pDataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;

	if (!debug)
	{
		printf("重定位表VirtualAddress地址: %#010X\r\n", RVA_BaseRelocationTable);
		printf("重定位表SizeOfBlock大小: %#010X\r\n", SizeOfBlock_BaseRelocationTable);
	}

	if (!RVA_BaseRelocationTable)
	{
		printf("这个程序没有导出表.\r\n");
		return 0;
	}

	//重定位表FOV地址，这里的FOA地址是为从 数据目录数组[5]获取的RVA并转换为FOA ， 目的是为了下面
	//偏移到FileBuffer中准确的BaseRelocation 重定位表起始地址
	DWORD FOA_BaseRelocationTable = RvaToOffset(pFileBuffer, RVA_BaseRelocationTable);

	//定位重定位表文件偏移的位置， 即：FileBuffer 的文件偏移
	pBaseRelocation = (PIMAGE_BASE_RELOCATION)((DWORD)pFileBuffer + FOA_BaseRelocationTable);

	if (!debug)
	{
		printf("重定位表FOA地址: %#010X\r\n", FOA_BaseRelocationTable);
		printf("重定位表文件偏移地址: %#010X\r\n", pBaseRelocation);
	}

	//定义 节 里面名称的数组表里，并置为 0    节Name 为8字节
	BYTE secName[9] = { 0 };  //这里是定义9个宽度的字节数组 并置为0，为后面的节操作做准备

	// 重定位表的偏移 和大小都不为 0 才执行
	for (DWORD i = 0; i < pBaseRelocation->SizeOfBlock && pBaseRelocation->VirtualAddress; i++)
	{
		// 参数pVirtualOfFOA_BaseReloc的FOA地址是从重定位表处获取的VirtualAddress将其转换为FOA地址；
		DWORD pVirtualOfFOA_BaseReloc = RvaToOffset(pFileBuffer, pBaseRelocation->VirtualAddress);

		// pSizeOfBlock_BaseReloc  存储具体项的数量
		DWORD pSizeOfBlock_BaseReloc = (pBaseRelocation->SizeOfBlock - 8) / 2;

		/*上面是根据VirtualAddress，SizeOfBlock总共占8个字节，SizeOfBlock是当前块的中大小
	  进行计算，为了算出真正具体项的数量，然后判断哪些是需要修改的项;

	  具体项宽度：2字节
	  也就是这个数据,内存中的页大小是1000H 也就是说2的12次方 就可以表示,一个页内所有的偏移地址
	  具体项的宽度是16字节高四位,代表类型：值为3代表的是需要修改的数据值为0代表的是,用于数据对齐的数据
	  可以不用修改.也就是说 我们只关注高4位的值为3的就可以了.
	  1000H --> 4096D --> 2的12次方
	  12 + 4 = 16 bit
	  */

	  //开始通过计算确定该结构所属哪个节里面
		for (DWORD j = 0; j < pPE->NumberOfSections; j++)
		{
			//pLowAddressOfFoa 节块起始偏移   pHighAddressOfFoa对齐前偏移
			DWORD pLowAddressOfFoa = RvaToOffset(pFileBuffer, pSect[i].VirtualAddress);
			DWORD pHighAddressOfFoa = RvaToOffset(pFileBuffer, pSect[i].Misc.VirtualSize);

			//  判断在那个节表内
			if (pVirtualOfFOA_BaseReloc >= pLowAddressOfFoa && pVirtualOfFOA_BaseReloc <= pHighAddressOfFoa)
			{
				//拷贝 名称
				memcpy(secName, pSect[i].Name, 8);
				break;
			}
		}
		//下面是打印本页的主要信息
		printf("节: %X ->重定位表VA: %#010X -> 节的名称:%s -> 具体项大小: %#010X\r\n", i, \
			pBaseRelocation->VirtualAddress, secName, pSizeOfBlock_BaseReloc);

		//打印一个页中所有重定位信息和地址

		//下面是通过偏移8个字节指向块中第一个具体项，因为宽度是2个字节，所以使用WORD并带指针类型
		WORD* recAddr = (WORD*)((BYTE*)pBaseRelocation + 0x8);

		for (DWORD n = 0; n < pSizeOfBlock_BaseReloc; n++)
		{
			/*下面算法解释：
		 第一行代码：通过获得的第一个具体项2个字节的地址与0x0FFF进行与操作，结果就去除了高4位;
		 然后就得到了准确的后面12位的偏移，刚好是咱想要的，直接按照算法来操作，使用该节所属的
		 VirtualAddress进行相加偏移，当然这里的VirtualAddress是需要转换为FOA的地址之后进行计算
		 此时便得到了准确需要偏移的值offset参数，通过这个参数进行偏移可得到准确的需要修改的偏移
		 地址，而参数type，就是我们所说的高4位代表一个类型，我们需要使用右移的方式将其置为0x0011
		 也就是3，所以代码中操作对其进行右移12位即可得到0x0011-->3;
		 这里回顾下右移：因为int如果是有符号的整形数,最左端的1位是符号位，0正1负，而现在我们的最
		 左端是0011，符号位是0表示正，那么右移的时候前面补0即可，所以移动12位置之后type参数的结果
		 就是0x0011->3

		 下面是计算其中一个节的具体数据例子：
		 节:0 -> 重定位表VA:0X00001000 -> 节的名称:.text -> 具体项大小:0X00000088
		 recAddr[j]:0X0000315F ---> 0x315F ---> 0011 0001 0101 1111

		 offset:0X0000115F     ---> 0011 0001 0101 1111 & 0000 1111 1111 1111 --->0x015F
		 0x015F + 0x1000 = 0x115F ---> offset:0X0000115F

		 type:0X00000003  ---> 0011 0001 0101 1111 >> 12 ---> 0000 0000 0000 0011 --> 0x0011 --> 3
		 0X0000215F,0X00000003
		 */
			DWORD pRepair_RvaOffset = (recAddr[n] & 0x0FFF) + pVirtualOfFOA_BaseReloc;

			//printf("recAddr[j]:%#010X \r\n",recAddr[j]);
			//printf("offset:%#010X \r\n",offset);
			WORD type = recAddr[n] >> 12;//三位
			//printf("type:%#010X \r\n",type);

			if (type != 0)
			{
				printf("%#010X,%#010X\r\n", pRepair_RvaOffset, type);
				//	system("pause");
			}
		}
		memset(secName, 0, 9);
		pBaseRelocation = (PIMAGE_BASE_RELOCATION)((BYTE*)pBaseRelocation + pBaseRelocation->SizeOfBlock);
	}
	return 0;
}


//测试
void PrintBaseRelocation()
{
	LPVOID pFileBuffer = NULL;
	DWORD FileBufferSize = 0;
	DWORD BaseName_FunctionAddr = 0;
	DWORD BaseOrdinals_FUnctionAddr = 0;

	//File-->FileBuffer
	FileBufferSize = ReadPEFile((char*)FilePath_In, &pFileBuffer);
	if (FileBufferSize == 0 || !pFileBuffer)
	{
		printf("文件-->缓冲区失败\r\n");
		return;
	}
	printf("FileBufferSize: %#X \r\n", FileBufferSize);

	GetDataDirectoyOfBaseRelocation(pFileBuffer);

	free(pFileBuffer);
}

int main(int argc, char* argv[])
{
	PrintBaseRelocation();

	return 0;
}