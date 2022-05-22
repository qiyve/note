#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

//用来判断.exe文件长度
int file_len(FILE* fp)
{
	int num = 0;
	//意思是把fp文件读写位置指针从SEEK_END开始后移0个字节.
	fseek(fp, 0, SEEK_END);

	//函数 ftell 用于得到文件位置指针当前位置相对于文件首的偏移字节数。
	num = ftell(fp);
	// 使用完毕后，要将文件指针指向文件开始
	fseek(fp, 0, SEEK_SET);

	//SEEK_SET	文件的开头
	//SEEK_CUR	文件指针的当前位置
	//SEEK_END	文件的末尾

	return num;
}

void func()
{
	//1、定义文件指针
	FILE* fp1 = NULL;
    //2/初始化exe文件长度
	int FpSize = 0;
	// 打开文件（读和写）
	fp1 = fopen("C:\\Windows\\System32\\notepad.exe", "rb");
	//获取exe大小
	FpSize = file_len(fp1);
	//申请内存
	char* FILE_f = (char*)malloc(FpSize);
	// 将.exe写入内存中
	if (FILE_f != NULL)
	{
		fread(FILE_f, FpSize, 1, fp1);
	}
	//返回内存编号
	int s = (int)FILE_f;
	printf("%x\n", s);
	//释放堆区
	free(FILE_f);
	fclose(fp1);
	
}

int main()
{
	func();


	return 0;
}


