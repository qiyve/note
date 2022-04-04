#include<stdlib.h>
#include<stdio.h>

int main(void)
{
	//cmd命令 cal：计算器  notepad：记事本   mspaint：画图板
	//system("calc");
	//system可以打开一个外部的应用程序，如果带路径 需要要用\\ 或者一个 /
	int value;
	value = system("cccc");
	//%d是一个占位符，表示输出一个整形数据
	printf("%d\n", value);

	return 0;
}