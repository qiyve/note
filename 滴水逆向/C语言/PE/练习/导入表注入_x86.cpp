#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


#define EVERYSECTIONTABLELENGTH 0x28
#define DLLNAME "InjectDll.dll"
#define DLLNAMELENGTH 0xE
#define FUNCTIONNAME "ExportFunction"
#define FUNCTIONNAMELENGTH 0xF
#define SECTIONNAME ".test"
#define INPUTFILENAME "D:/ipmsg.exe"
#define INPUTMODE "rb"
#define OUTPUTFILENAME "test.exe"
#define OUTPUTMODE "wb"


/*************************************************
函数功能：读取一个文件,将文件内容写入到内存中;
函数参数：无
函数返回值：pFileBuffer(LPVOID)
**************************************************/
LPVOID FileBuffer() {
    FILE* pFile = NULL;    //文件指针
    LPVOID pFileBuffer = NULL; //存放数据内存的首地址
    DWORD filesize = 0;//记录文件大小
    size_t result = 0;//记录写入的返回结果

    //打开一个文件
    pFile = fopen(INPUTFILENAME, INPUTMODE);
    if (pFile == NULL) {
        printf("打开文件失败!\n");
        return NULL;
    }

    //统计文件的大小
    fseek(pFile, 0, SEEK_END);
    filesize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    //申请一块内存
    pFileBuffer = malloc(filesize);
    if (pFileBuffer == NULL) {
        printf("申请内存失败!\n");
        fclose(pFile);
        return NULL;
    }

    //将文件数据写入内存
    result = fread(pFileBuffer, 1, filesize, pFile);
    if (result != filesize) {
        printf("文件写入内存失败!\n");
        fclose(pFile);
        free(pFileBuffer);
        return NULL;
    }

    fclose(pFile);
    return pFileBuffer;
}

/*************************************************
函数功能：返回对齐后的大小；
函数参数：virtualsize(原有长度)，alignment(对齐方式)
函数返回值：ret(int型)
**************************************************/
DWORD AlignSize(DWORD virtualsize, DWORD alignment) {
    DWORD ret = alignment;
    if (virtualsize <= alignment) {
        return ret;
    }
    else {
        ret = (virtualsize / alignment) * alignment + alignment;
        return ret;
    }
}

/*************************************************
函数功能：计算一个filebuffer的大小；
函数参数：pFileBuffer(LPVOID)
函数返回值：filesize(int)
**************************************************/
DWORD CountFileBufferSize(LPVOID pFileBuffer) {
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    DWORD filesize = 0;//记录文件大小

    if (pFileBuffer == NULL) {
        printf("文件写入内存失败!\n");
        return NULL;
    }

    //判读是否具有MZ标志                                                                                           
    if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE) {
        printf("不具有MZ标志!\n");
        free(pFileBuffer);
        return 0;
    }

    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;

    //判断是否具有PE标志                                                                                           
    if (*(PDWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew) != IMAGE_NT_SIGNATURE) {
        printf("不具有PE标志\n");
        free(pFileBuffer);
        return 0;
    }

    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 4);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + 20);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //最后一个节头地址 + 最后一节大小
    filesize = (DWORD)((pSectionHeader + pPEHeader->NumberOfSections - 1)->PointerToRawData + (pSectionHeader + pPEHeader->NumberOfSections - 1)->SizeOfRawData);
    return filesize;
}

/*************************************************
函数功能：计算一个文件大小；
函数参数：filename(文件的绝对路径,LPSTR),mode(读取文件的形式，LPSTR)
函数返回值：filesize(int)
**************************************************/
DWORD CountFileSize(LPSTR filename, LPSTR mode) {
    FILE* pFile = NULL;
    LPSTR pFileBuffer = NULL;
    DWORD filesize = 0;

    //打开文件
    pFile = fopen(filename, mode);
    if (pFile == NULL) {
        printf("打开文件失败!\n");
        return NULL;
    }

    //统计文件大小
    fseek(pFile, 0, SEEK_END);
    filesize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    fclose(pFile);
    return filesize;
}


/*************************************************
函数功能：PE文件尾部新增一个节；
函数参数：pFileBuffer(LPVOID),sectionLength(DWORD)
函数返回值：pNewFileBuffer(LPVOID)
**************************************************/
LPVOID AddLastSection(LPVOID pFileBuffer, DWORD sectionLength) {
    LPVOID pNewFileBuffer = NULL;
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;

    if (pFileBuffer == NULL) {
        printf("文件写入内存失败!\n");
        return NULL;
    }

    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x4);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + 0x14);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //判断节表空间是否足够,节表后需要预留一个节表空间的位置
    if (pSectionHeader->PointerToRawData - (DWORD)(pSectionHeader + pPEHeader->NumberOfSections) < 0x50) {
        printf("节表空间不够!\n");
        free(pFileBuffer);
        return NULL;
    }

    //开辟新的内存
    DWORD filesize = CountFileBufferSize(pFileBuffer);
    pNewFileBuffer = malloc(filesize + sectionLength);
    if (pNewFileBuffer == NULL) {
        printf("申请内存失败!\n");
        free(pFileBuffer);
        return NULL;
    }

    //新内存初始化为0
    memset(pNewFileBuffer, 0, filesize + sectionLength);

    //拷贝原来的文件内容到新内存并释放旧文件内存
    memcpy(pNewFileBuffer, pFileBuffer, filesize);
    free(pFileBuffer);

    //结构体指针再次初始化
    pDosHeader = (PIMAGE_DOS_HEADER)pNewFileBuffer;
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pNewFileBuffer + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 4);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + 20);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //修改sizeofimage
    pOptionHeader->SizeOfImage += sectionLength;

    //copy第一个节表内容
    memcpy(pSectionHeader + pPEHeader->NumberOfSections, pSectionHeader, EVERYSECTIONTABLELENGTH);

    //修改新增的节表的项目
    PIMAGE_SECTION_HEADER changeSection1 = pSectionHeader + pPEHeader->NumberOfSections;//新增节表首地址
    PIMAGE_SECTION_HEADER changeSection2 = pSectionHeader + pPEHeader->NumberOfSections - 1;//新增节表的前一个节表首地址
    changeSection1->Misc.VirtualSize = sectionLength;//修改内存中的尺寸
    changeSection1->SizeOfRawData = sectionLength;//修改文件中的尺寸
    changeSection1->Characteristics = 0xc0000040;
    memcpy(changeSection1, SECTIONNAME, 0x6);//修改名字

    changeSection1->PointerToRawData = changeSection2->PointerToRawData + changeSection2->SizeOfRawData;

    if (changeSection2->SizeOfRawData > changeSection2->Misc.VirtualSize) {
        changeSection1->VirtualAddress = changeSection2->VirtualAddress + changeSection2->SizeOfRawData;
    }
    else {
        changeSection1->VirtualAddress = changeSection2->VirtualAddress + changeSection2->Misc.VirtualSize;
    }

    //修改NumberOfSections
    pPEHeader->NumberOfSections += 1;

    return pNewFileBuffer;
}


/*************************************************
函数功能：将RVA的值转换成FOA；
函数参数：pFileBuffer(LPVOID),virtualAddress(LPSTR)
函数返回值：fileAddress(LPVOID)
**************************************************/
LPVOID RvaToFoa(LPVOID pFileBuffer, LPSTR virtualAddress) {
    LPSTR sectionAddress = NULL;//记录距离节头的距离
    LPSTR fileAddress = NULL;//记录文件中的偏移
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;

    if (pFileBuffer == NULL) {
        printf("文件写入内存失败!\n");
        return NULL;
    }

    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 4);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + 20);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    if ((DWORD)virtualAddress <= pOptionHeader->SizeOfHeaders) {
        return virtualAddress;
    }

    for (DWORD i = 1; i <= pPEHeader->NumberOfSections; i++) {
        if ((DWORD)virtualAddress < pSectionHeader->VirtualAddress) {
            pSectionHeader--;
            break;
        }
        else if (i == pPEHeader->NumberOfSections) {
            break;
        }
        else {
            pSectionHeader++;
        }

    }

    //距离该节头的距离
    sectionAddress = virtualAddress - pSectionHeader->VirtualAddress;
    fileAddress = pSectionHeader->PointerToRawData + sectionAddress;

    return (LPVOID)fileAddress;
}


/*************************************************
函数功能：将FOA的值转换成RVA;
函数参数：pFileBuffer（LPVOID）,virtualAddress（LPSTR）
函数返回值：fileAddress（LPVOID）
**************************************************/
LPVOID FoaToRva(LPVOID pFileBuffer, LPSTR fileaddress) {
    LPSTR sectionAddress = NULL;//记录距离节头的距离
    LPSTR virtualaddress = NULL;//记录内存中的偏移
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;

    if (pFileBuffer == NULL) {
        printf("文件写入内存失败!\n");
        return NULL;
    }

    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 4);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + 20);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    if ((DWORD)fileaddress <= pOptionHeader->SizeOfHeaders) {
        return fileaddress;
    }

    for (DWORD i = 1; i <= pPEHeader->NumberOfSections; i++) {
        if ((DWORD)fileaddress < pSectionHeader->PointerToRawData) {
            pSectionHeader--;
            break;
        }
        else if (i == pPEHeader->NumberOfSections) {
            break;
        }
        else {
            pSectionHeader++;
        }

    }

    //距离该节头的距离
    sectionAddress = fileaddress - pSectionHeader->PointerToRawData;
    virtualaddress = pSectionHeader->VirtualAddress + sectionAddress;

    return (LPVOID)virtualaddress;
}


/*************************************************
函数功能：导入表注入;
函数参数：pFileBuffer(LPVOID)
函数返回值：无
**************************************************/
void MoveImportTable(LPVOID pFileBuffer)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;

    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    PIMAGE_DATA_DIRECTORY pDataDirectory = NULL;//定位表目录
    PIMAGE_IMPORT_DESCRIPTOR importTableAddress = NULL;//定位导入表的真正位置
    LPVOID returnAddress = NULL;//记录RVAtoFOA的返回值

    if (pFileBuffer == NULL) {
        printf("文件写入内存失败!\n");
        return;
    }

    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x4);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + 0x14);
    //定位导入表目录位置(第二个表)
    pDataDirectory = (PIMAGE_DATA_DIRECTORY)pOptionHeader->DataDirectory;
    pDataDirectory += 0x1;

    //计算新增节的大小 = 原导入表大小 + 新增导入表大小 + INT + IAT + dllname + _IMAGE_IMPORT_BY_NAME大小
    DWORD sectionLength = pDataDirectory->Size + 0x28 + +0x10 + DLLNAMELENGTH + FUNCTIONNAMELENGTH + 0x2;
    sectionLength = AlignSize(sectionLength, pOptionHeader->FileAlignment);

    //新增一个节
    LPVOID pNewFileBuffer = AddLastSection(pFileBuffer, sectionLength);

    if (pNewFileBuffer == NULL) {
        printf("新增节失败!\n");
        return;
    }

    pDosHeader = (PIMAGE_DOS_HEADER)pNewFileBuffer;
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pNewFileBuffer + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x4);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + 0x14);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);
    //定位导入表目录位置(第二个表)
    pDataDirectory = (PIMAGE_DATA_DIRECTORY)pOptionHeader->DataDirectory;
    pDataDirectory += 0x1;

    //定位到新节的位置和导入表的位置
    PDWORD pNewSection = (PDWORD)((pSectionHeader + pPEHeader->NumberOfSections - 1)->PointerToRawData + (DWORD)pNewFileBuffer);
    returnAddress = RvaToFoa(pNewFileBuffer, (LPSTR)pDataDirectory->VirtualAddress);
    importTableAddress = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)returnAddress + (DWORD)pNewFileBuffer);

    //复制原导入表
    memcpy(pNewSection, importTableAddress, pDataDirectory->Size);

    //原导入表后新增一个导入表
    importTableAddress = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)pNewSection + pDataDirectory->Size - 0x14);

    //增加8字节INT表
    PIMAGE_THUNK_DATA32 pIntTable = (PIMAGE_THUNK_DATA32)((DWORD)importTableAddress + 0x28);//保留20字节的0
    PIMAGE_THUNK_DATA32 repairIntTable = pIntTable;
    pIntTable++;
    pIntTable->u1.Ordinal = 0x0;
    pIntTable++;

    //增加8字节IAT表
    PIMAGE_THUNK_DATA32 pIatTable = (PIMAGE_THUNK_DATA32)(pIntTable);
    PIMAGE_THUNK_DATA32 repairIatTable = pIatTable;
    pIatTable++;
    pIatTable->u1.Ordinal = 0x0;
    pIatTable++;

    //分配空间存储DLL名称字符串
    PDWORD dllNameAddress = (PDWORD)pIatTable;
    memcpy(dllNameAddress, DLLNAME, DLLNAMELENGTH);

    //增加IMAGE_IMPORT_BY_NAME 结构
    PIMAGE_IMPORT_BY_NAME functionNameAddress = (PIMAGE_IMPORT_BY_NAME)((DWORD)dllNameAddress + DLLNAMELENGTH);
    PDWORD pFunctionName = (PDWORD)((DWORD)functionNameAddress + 0x2);
    memcpy(pFunctionName, FUNCTIONNAME, FUNCTIONNAMELENGTH);

    //将IMAGE_IMPORT_BY_NAME结构的RVA赋值给INT和IAT表中的第一项
    repairIntTable->u1.AddressOfData = (DWORD)FoaToRva(pNewFileBuffer, (LPSTR)((DWORD)functionNameAddress - (DWORD)pNewFileBuffer));
    repairIatTable->u1.AddressOfData = repairIntTable->u1.Ordinal;

    //修正导入表Name、OriginalFirstThunk、FirstThunk
    importTableAddress->Name = (DWORD)FoaToRva(pNewFileBuffer, (LPSTR)((DWORD)dllNameAddress - (DWORD)pNewFileBuffer));
    importTableAddress->OriginalFirstThunk = (DWORD)FoaToRva(pNewFileBuffer, (LPSTR)((DWORD)repairIntTable - (DWORD)pNewFileBuffer));
    importTableAddress->FirstThunk = (DWORD)FoaToRva(pNewFileBuffer, (LPSTR)((DWORD)repairIatTable - (DWORD)pNewFileBuffer));

    //修正IMAGE_DATA_DIRECTORY结构的VirtualAddress和Size
    pDataDirectory->VirtualAddress = (DWORD)FoaToRva(pNewFileBuffer, (LPSTR)((DWORD)pNewSection - (DWORD)pNewFileBuffer));
    pDataDirectory->Size += 0x14;

    //存盘
    FILE* pFile = NULL;
    DWORD newfilesize = 0;
    size_t newresult = 0;

    pFile = fopen(OUTPUTFILENAME, OUTPUTMODE);
    if (pFile == NULL) {
        printf("打开文件失败!\n");
        free(pNewFileBuffer);
        return;
    }

    newfilesize = CountFileSize((LPSTR)INPUTFILENAME, (LPSTR)INPUTMODE) + sectionLength;
    newresult = fwrite(pNewFileBuffer, 1, newfilesize, pFile);

    if (newresult != newfilesize) {
        printf("写入文件失败!\n");
        fclose(pFile);
        free(pNewFileBuffer);
        return;
    }

    printf("存盘成功!\n");
    fclose(pFile);
    free(pNewFileBuffer);
}

int main() 
{
    LPVOID pFileBuffer = FileBuffer();
    MoveImportTable(pFileBuffer);
    return 0;
}