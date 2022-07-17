#include<stdio.h>
#include <windows.h>

DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	for (int i = 0; i <1000; i++)
	{
		printf("+++++++++\n");
		Sleep(1000);
	}
	return 0;
}



int main01(int argc, char* argv[])
{

	//创建一个新的线程				
	HANDLE hThread1 = ::CreateThread(NULL, 0, ThreadProc1,
		NULL, 0, NULL);

	//参数1：内核对象句柄，可以是进程，也可以是线程    //参数2：等待时间，单位毫秒   INFINITE -1  表示一直等
	// 超时返回 0x102
	DWORD dwCode = ::WaitForSingleObject(hThread1, 1000);
	printf("%x\n", dwCode);
	MessageBox(0, 0, 0, 0);

	return 0;
}


DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	for (int i = 0; i < 10; i++)
	{
		printf("+++++++++\n");
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	for (int i = 0; i < 30; i++)
	{
		printf("---------\n");
		Sleep(1000);
	}

	return 0;
}


int main(int argc, char* argv[])
{
	
	HANDLE hArray[2];

	//创建一个新的线程						
	hArray[0] = ::CreateThread(NULL, 0, ThreadProc2,
		NULL, 0, NULL);

	//创建一个新的线程						
	hArray[1] = ::CreateThread(NULL, 0, ThreadProc3,
		NULL, 0, NULL);

	/*参数1：内核对象数量， 参数2：内核对象数组，   参数4：超时时间 INFINITE一直等待
	参数3：等到类型 TRUE 等到所有变为已通知，FALSE只要有一个变为已通知并返回最先变为已通知的内核对象下标 
	 */
	DWORD dwCode = ::WaitForMultipleObjects(2, hArray, TRUE, 3000);
	printf("%x\n", dwCode);
	MessageBox(0, 0, 0, 0);

	return 0;
}

