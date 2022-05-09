#include<iostream>
using namespace std;

//1、用__declspec(naked)裸函数实现下面的功能
//练习目的：
//(1) 熟悉堆栈结构
//(2) 参数、局部变量的位置
//(3) 返回值存储的位置

//int plus(int x, int y, int z)					010101010
//{
//	int a = 2;
//	int b = 3;
//	int c = 4;
//	return x + y + z + a + b + c;
//}
int __declspec(naked)Plus(int x, int y, int z)
{
	__asm
	{
		//保存栈底
		push ebp
		//提升堆栈
		mov ebp, esp
		sub esp, 0x40
		//保存现场
		push ebx
		push esi
		push edi
		//填充缓存区
		mov eax, 0xCCCCCCCC
		mov ecx, 0x10
		lea edi, dword ptr ds : [ebp - 0x40]
		rep stosd		
		//该方法真正要执行的功能

		//局部变量 ebp-4      参数ebp+8
		mov dword ptr ds : [ebp - 0x4] , 2
		mov dword ptr ds : [ebp - 0x8] , 3
		mov dword ptr ds : [ebp - 0xc] , 4		

		mov eax, dword ptr ds : [ebp + 0x8]
		add eax, dword ptr ds : [ebp + 0xc]
		add eax, dword ptr ds : [ebp + 0x10]

		add eax, dword ptr ds : [ebp - 0x4]
		add eax, dword ptr ds : [ebp - 0x8]
		add eax, dword ptr ds : [ebp - 0xc]

		//恢复现场
		pop edi
		pop esi
		pop ebx
		//降低堆栈
		mov esp, ebp
		pop ebp

		ret
	}

}

int main()
{
	int a = Plus(1, 2, 3);
	cout << a;

	return 0;
}