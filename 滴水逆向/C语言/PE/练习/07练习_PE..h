// gbpeall.h: interface for the gbpeall class.
//
//////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#if !defined(AFX_GBPEALL_H__C24C6881_E003_41F7_BE14_24DDA1702CCD__INCLUDED_)
#define AFX_GBPEALL_H__C24C6881_E003_41F7_BE14_24DDA1702CCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>


#define debug 1
//#define FILEPATH_IN         "C:\\WINDOWS\\system32\\kernel32.dll"
//    #define FilePath_In         "C:\\cntflx\\notepad.exe"
#define FilePath_In         "ipmsg.exe"
//#define FilePath_Out        "C:\\cntflx\\notepadnewpes.exe"
//#define FilePath_Out        "C:\\cntflx\\ipmsgnewpeaddcodes.exe"
//#define FilePath_Out        "C:\\cntflx\\ipmsgnewaddsections.exe"
//#define FilePath_Out        "C:\\cntflx\\ipmsgextendsections.exe"
#define FilePath_Out        "ipmsg_cntf_merge.exe"
#define MESSAGEBOXADDR      0x77D5050B
#define SHELLCODELENGTH     0x12 //16进制的，转换为十进制就是18

extern BYTE ShellCode[];

//读文件 --->FileBuffer
DWORD ReadPEFile(IN const char* lpszFile, OUT LPVOID* pFileBuffer);

//写到ImageBuffer,FileBuffer ---> ImageBuffer
DWORD CopyFileBufferToImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID* pImageBuffer);

//写到NewImageBuffer, FileBuffer ---> NewImageBuffer
DWORD CopyFileBufferToNewImageBuffer(IN LPVOID pFileBuffer, IN size_t fileSize, OUT LPVOID* pNewImageBuffer);

//写到NewImageBuffer, 这里供扩大节使用；
DWORD FileBufferToModifyImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID* pNewImageBuffer);

//写入到NewBuffer，目的是将拉伸后的ImageBuffer再缩回来，为存盘准备
DWORD CopyImageBufferToNewBuffer(IN LPVOID pImageBuffer, OUT LPVOID* pNewBuffer);

//写入到NewImageBuffer，这里供合并节使用
DWORD ImageBufferMergeSections(IN LPVOID pImageBuffer, OUT LPVOID* pNewBuffer);

//写到pNewBuffer里面，从pNewImageBuffer写入 ---> pNewBuffer
//DWORD ModifyImageBufferToNewBuffer(IN LPVOID pNewImageBuffer,OUT LPVOID* pNewBuffer);

//Rva转Foa
DWORD RvaToFileOffset(IN LPVOID pFileBuffer, IN DWORD dwRva);

//Foa转RVA
DWORD FoaToImageOffset(IN LPVOID pFileBuffer, IN DWORD dwFoa);

//对齐大小
DWORD AlignLength(DWORD Actuall_size, DWORD Align_size);

//另一种对齐计算方式
DWORD Alignment(DWORD alignment_value, DWORD addend, DWORD address);

//将MemBuffer写入到硬盘，这里就是将各种修改好的内存文件，存入到本地硬盘中；
BOOL MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT const char* lpszFile);

//DWORD RvaToFileOffset(IN LPVOID pFileBuffer,IN DWORD dwRva);

//调用函数，添加ShellCode代码
VOID AddCodeInCodeSec();  //这个调用函数用到下面的4个函数
//ReadPEFile CopyFileBufferToImageBuffer CopyImageBufferToNewBuffer MemeryTOFile

//调用函数，新增节表和节操作；
VOID NewSectionsInCodeSec();  //这个调用函数用到下面的3个函数
//ReadPEFile CopyFileBufferToNewImageBuffer MemeryTOFile

//调用函数，扩大最后一个节
VOID ExtendLastSectionsInCodeSec(); //这个调用函数用到下面的4个函数
//ReadPEFile FileBufferToModifyImageBuffer CopyImageBufferToNewImageBuffer MemeryTOFile

//调用函数，合并节
VOID ModifySectionsOneInCodeSec(); //这个调用函数用到下面的4个函数
//ReadPEFile CopyFileBufferToImageBuffer FileBufferToModifyOneImageBuffer MemeryTOFile

//调用函数，Rva和Foa之间的相互转换；
VOID RvaAndFoaConversion(); //这个调用函数用到下面的3个函数
//ReadPEFile RvaToFileOffset FoaToImageOffset

#endif // !defined(AFX_GBPEALL_H__C24C6881_E003_41F7_BE14_24DDA1702CCD__INCLUDED_)