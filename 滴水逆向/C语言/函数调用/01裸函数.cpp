#include<iostream>
using namespace std;

//裸函数 关键字 __declspec(naked)  
//注意：编译器不会自动生成任何代码需要自写， 必须加 __asm {ret}否则无法运行
int __declspec(naked)Plus(int x, int y)
{
	__asm
	{
		//保存调用前栈低
		push ebp
		//提升堆栈
		mov ebp, esp
		sub esp, 0x40
		//保存现场
		push ebx
		push esi
		push edi
		//填充缓存空间
		mov eax, 0xcccccccc
		mov ecx, 0x10
		lea edi, dword ptr ds:[ebp - 0x40]
		rep stosd
		//函数功能
		mov eax, dword ptr ds : [ebp + 0x8]
		add eax, dword ptr ds : [ebp + 0xc]
		//恢复现场  堆栈 先进后出
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
	Plus(1, 2);


	return 0;
}
