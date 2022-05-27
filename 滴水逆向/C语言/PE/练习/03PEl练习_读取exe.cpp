#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#define FILEPATH "C:\\Windows\\System32\\notepad.exe"

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
LPVOID fRead01()
{
	FILE* file = NULL;
	errno_t a = fopen_s(&file, FILEPATH, "rb");
	if (a != 0)
	{
		printf("打开失败\n");
		return 0;
	}
	fseek(file, 0, SEEK_END);
	size_t b = ftell(file);
	fseek(file, 0, SEEK_SET);
	LPVOID buff = malloc(b);
	if (buff == 0)
	{
		printf("分配内存失败\n");
		fclose(file);
		return 0;
	}
	size_t c = fread(buff, b, 1, file);
	if (c == 0 || c > 1)
	{
		printf("读取失败\n");
		fclose(file);
		free(buff);
		return 0;
	}
	printf("读取成功\n");
	fclose(file);
	return buff;
}

void showSectionHeader()
{
	//无类型指针
	LPVOID buff = NULL;
	//DOS头指针
	PIMAGE_DOS_HEADER DosHeader = NULL;
	//NT头
	PIMAGE_NT_HEADERS ntHeader = NULL;
	//标准PE头
	PIMAGE_FILE_HEADER peHeader = NULL;
	//可选PE
	PIMAGE_OPTIONAL_HEADER32 OptionHeader = NULL;
	//节表
	PIMAGE_SECTION_HEADER SectionHeader = NULL;;

	buff = fRead01();

	//判断dos头
	DosHeader = (PIMAGE_DOS_HEADER)buff;
	//DWORD e_magic为"MZ",定义为IMAGE_DOS_SIGNATURE
	DosHeader = (PIMAGE_DOS_HEADER)buff;
	if (DosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		printf("不是MZ标记\n");
		return;
	}
	//判断PE标记
	ntHeader = (PIMAGE_NT_HEADERS)((DWORD)buff + DosHeader->e_lfanew);
	if (ntHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		printf("不是PE标记\n");
		free(buff);
		return;
	}
	printf("PE:%x\n", ntHeader->Signature);

	//NumberOfSections 记录节表和位置
	peHeader = (PIMAGE_FILE_HEADER)((DWORD)ntHeader + 4);
	printf("节的数量:%x\n", peHeader->NumberOfSections);
	printf("可选PE头的大小:%x\n", peHeader->SizeOfOptionalHeader);

	//可选PE头   标准PE大小为20
	OptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)peHeader + 20);
	printf("内存对齐为：%x\n", OptionHeader->SectionAlignment);
	printf("文件对齐为：%x\n", OptionHeader->FileAlignment);
	
	//OptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)peHeader + 20);
	//printf("内存对齐:%x\n", OptionHeader->SectionAlignment);
	//printf("文件对齐:%x\n", OptionHeader->FileAlignment);


	//节表  32位E0  64位 F0
	int Section_number = peHeader->NumberOfSections; 
	SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)OptionHeader + peHeader->SizeOfOptionalHeader);

	for (int i = 0; i < Section_number; i++)
	{
		printf("------------节表信息%d------------\n", i + 1);
		printf("节表名字(name):%s\n", SectionHeader->Name);
		printf("节表对齐前尺寸：%x\n", SectionHeader->Misc);
		printf("VirualAddress(内存偏移)%x\n", SectionHeader->VirtualAddress);
		printf("SizeOfRawDate(文件对齐后大小:%x\n", SectionHeader->SizeOfRawData);
		printf("PointerToRawDate(文件的偏移)%x\n", SectionHeader->PointerToRawData);
		printf("Characteristics(节的属性)%x\n", SectionHeader->Characteristics);
		//偏移读取下一个节表
		SectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)SectionHeader + 40);
		printf("\n\n");
	}

	free(buff);
}

int main()
{

	showSectionHeader();


	return 0;
}
