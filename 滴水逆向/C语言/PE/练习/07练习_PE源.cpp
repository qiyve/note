#include"源.h"

//定义一个全局变量
BYTE ShellCode[] =
{
    0x6A,00,0x6A,00,0x6A,00,0x6A,00, //MessageBox push 0的硬编码
    0xE8,00,00,00,00,  // call汇编指令E8和后面待填充的硬编码
    0xE9,00,00,00,00   // jmp汇编指令E9和后面待填充的硬编码
};

// allpelx.cpp : Defines the entry point for the console application.
//


int main()
{
    //Fun();
    //AddCodeInCodeSec();
    //NewSectionsInCodeSec();
    //ExtendLastSectionsInCodeSec();
    ModifySectionsOneInCodeSec();
    //RvaAndFoaConversion();

    system("pause");
    return 0;
}