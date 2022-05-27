#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

//IMAGE_SIZEOF_FILE_HEADER 20   标准PE大小
/*
IMAGE_SECTIONAL_HEADER   节表
Name 节表名字
Micsc.VirtualSize 该节文件对齐前真实尺寸   Misc
ViruakAddress 节拉伸后 开始的地方
SizeOfRawData 节在文件中对齐后的大小
PointerToRawDate 节在文件中开始的地方
Characteristice	节的属性
*/
//LPVOID是一个没有类型的指针，也就是说你可以将任意类型的指针赋值给LPVOID类型的变量（一般作为参数传递），
//然后在使用的时候再转换回来。 可以将其理解为long型的指针，指向void型
LPVOID ReadPEFile()
{
	FILE* pFile = NULL;
	//记录大小
	//DWORD 代表 unsigned long
	DWORD fileSize = 0;
	//文件缓冲区
	LPVOID pFileBuffer = NULL;

	//打开文件	
	int a = fopen_s(&pFile,"D:\\ipmsg.exe ","rb");
	if (!pFile)
	{
		printf(" 无法打开 EXE 文件! ");
		return NULL;
	}
	//读取文件大小		
	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	//分配缓冲区	
	pFileBuffer = malloc(fileSize);

	if (!pFileBuffer)
	{
		printf(" 分配空间失败! ");
		fclose(pFile);
		return NULL;
	}
	//将文件数据读取到缓冲区	
	size_t n = fread(pFileBuffer, fileSize, 1, pFile);
	if (!n)
	{
		printf(" 读取数据失败! ");
		free(pFileBuffer);
		fclose(pFile);
		return NULL;
	}
	//关闭文件	
	fclose(pFile);
	return pFileBuffer;
}

void PrintNTHeaders()
{
	LPVOID pFileBuffer = NULL;
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;

	pFileBuffer = ReadPEFile();
	if (!pFileBuffer)
	{
		printf("文件读取失败\n");
		return;
	}

	//判断是否是有效的MZ标志	
	if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
	{
		printf("不是有效的MZ标志\n");
		free(pFileBuffer);
		return;
	}
	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	//打印DOC头	
	printf("********************DOC头********************\n");
	printf("MZ标志：%x\n", pDosHeader->e_magic);
	printf("PE偏移：%x\n", pDosHeader->e_lfanew);
	//判断是否是有效的PE标志	
	if (*((PDWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("不是有效的PE标志\n");
		free(pFileBuffer);
		return;
	}
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
	//打印NT头	
	printf("********************NT头********************\n");
	printf("NT：%x\n", pNTHeader->Signature);
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);
	printf("********************PE头********************\n");
	printf("PE：%x\n", pPEHeader->Machine);
	printf("节的数量：%x\n", pPEHeader->NumberOfSections);
	printf("SizeOfOptionalHeader：%x\n", pPEHeader->SizeOfOptionalHeader);
	//可选PE头	
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
	printf("********************OPTIOIN_PE头********************\n");
	printf("OPTION_PE：%x\n", pOptionHeader->Magic);
	//释放内存	
	free(pFileBuffer);
}


int main()
{

	//PrintNTHeaders();
	DWORD fileSize = 2;

	return 0;
}
