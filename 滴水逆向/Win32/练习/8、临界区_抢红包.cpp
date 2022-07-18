#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include"resource.h"


//创建文本对话框句柄
HWND hongbao;  //IDC_EDIT_1  存储红包数量对话框
HWND zg;  //IDC_EDIT_2   抢红包线程1
HWND wst;  //IDC_EDIT_3  抢红包线程2
HWND smy;  //IDC_EDIT_4  抢红包线程3

//创建临界区结构对象
CRITICAL_SECTION cs;
DWORD num;   //红包值

//  zg 
DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	while (num > 0)
	{
		//创建令牌
		EnterCriticalSection(&cs);
		//获取 红包 文本框内容
		CHAR szBuffer[10];
		memset(szBuffer, 0, 10);
		GetWindowTextA(hongbao, szBuffer, 10);

		//获取 zg 文本对话框内容
		CHAR zgBuffer[10];
		memset(zgBuffer, 0, 10);
		GetWindowTextA(zg, zgBuffer, 10);

		//字符串转数字
		sscanf(szBuffer, "%d", &num);
		DWORD zgNum; //存储抢到的红包值
		sscanf(zgBuffer, "%d", &zgNum);
		if (num >= 50)
		{
			memset(szBuffer, 0, 10);
			memset(zgBuffer, 0, 10);
			//每次抢 50；
			num -= 50;
			zgNum += 50;
			//数字转字符
			sprintf(szBuffer, "%d", num);
			sprintf(zgBuffer, "%d", zgNum);
			//写回文本对话框
			SetWindowTextA(hongbao, szBuffer);
			SetWindowTextA(zg, zgBuffer);
		}
		LeaveCriticalSection(&cs);
		Sleep(1000);
	}
	return 0;
}

//wst
DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	while (num > 0)
	{
		//创建令牌
		EnterCriticalSection(&cs);
		//获取 红包 文本框内容
		CHAR szBuffer[10];
		memset(szBuffer, 0, 10);
		GetWindowTextA(hongbao, szBuffer, 10);

		//获取 wst 文本对话框内容
		CHAR zgBuffer[10];
		memset(zgBuffer, 0, 10);
		GetWindowTextA(wst, zgBuffer, 10);

		//字符串转数字
		sscanf(szBuffer, "%d", &num);
		DWORD zgNum; //存储抢到的红包值
		sscanf(zgBuffer, "%d", &zgNum);
		if (num >= 50)
		{
			memset(szBuffer, 0, 10);
			memset(zgBuffer, 0, 10);
			//每次抢 50；
			num -= 50;
			zgNum += 50;
			//数字转字符
			sprintf(szBuffer, "%d", num);
			sprintf(zgBuffer, "%d", zgNum);
			//写回文本对话框
			SetWindowTextA(hongbao, szBuffer);
			SetWindowTextA(wst, zgBuffer);
		}
		LeaveCriticalSection(&cs);
		Sleep(1000);
	}
	return 0;
}

//smy
DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	while (num > 0)
	{
		//创建令牌
		EnterCriticalSection(&cs);
		//获取 红包 文本框内容
		CHAR szBuffer[10];
		memset(szBuffer, 0, 10);
		GetWindowTextA(hongbao, szBuffer, 10);

		//获取 wst 文本对话框内容
		CHAR zgBuffer[10];
		memset(zgBuffer, 0, 10);
		GetWindowTextA(smy, zgBuffer, 10);

		//字符串转数字
		sscanf(szBuffer, "%d", &num);
		DWORD zgNum; //存储抢到的红包值
		sscanf(zgBuffer, "%d", &zgNum);
		if (num >= 50)
		{
			memset(szBuffer, 0, 10);
			memset(zgBuffer, 0, 10);
			//每次抢 50；
			num -= 50;
			zgNum += 50;
			//数字转字符
			sprintf(szBuffer, "%d", num);
			sprintf(zgBuffer, "%d", zgNum);
			//写回文本对话框
			SetWindowTextA(hongbao, szBuffer);
			SetWindowTextA(smy, zgBuffer);
		}
		LeaveCriticalSection(&cs);
		Sleep(1000);
	}
	return 0;
}


//线程函数
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	//初始化令牌
	InitializeCriticalSection(&cs);

	//创建线程
	HANDLE hThread1 = ::CreateThread(NULL, 0, ThreadProc1, NULL, 0, NULL);
	HANDLE hThread2 = ::CreateThread(NULL, 0, ThreadProc2, NULL, 0, NULL);
	HANDLE hThread3 = ::CreateThread(NULL, 0, ThreadProc3, NULL, 0, NULL);

	return 0;
}

//回调函数  消息处理
BOOL CALLBACK DialogProc(HWND   hwndDlg,
						 UINT   uMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			hongbao = GetDlgItem(hwndDlg, IDC_EDIT_1); //获取红包对话框句柄
			zg = GetDlgItem(hwndDlg, IDC_EDIT_2);    // 获取强红包对话框1 句柄
			wst = GetDlgItem(hwndDlg, IDC_EDIT_3);     // 2
			smy = GetDlgItem(hwndDlg, IDC_EDIT_4);    // 3

			//初始化值
			SetWindowText(hongbao, TEXT("1000"));
			SetWindowText(zg, TEXT("0"));
			SetWindowText(wst, TEXT("0"));
			SetWindowText(smy, TEXT("0"));

			return TRUE;
		}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			{
				//获取文本对话框内容
				CHAR szBuffer[10];
				memset(szBuffer, 0, 10);
				GetWindowTextA(hongbao, szBuffer, 10);
				//字符转数字
				sscanf(szBuffer, "%d", &num);

				//清空输入框
				SetWindowText(zg, TEXT("0"));
				SetWindowText(wst, TEXT("0"));
				SetWindowText(smy, TEXT("0"));

				HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
				//如果不在其他地方引用它 关闭句柄
				::CloseHandle(hThread);
				return TRUE;
			}

		}
		break;
	case WM_CLOSE: //退出
		EndDialog(hwndDlg, 0);
		return TRUE;
	}
	

	return FALSE;
}
int CALLBACK WinMain(HINSTANCE hInstance,
				   	 HINSTANCE hPrevHinstance,
					 LPSTR	   lpCmdLine,
					 int	   nCmdShow)
{
	//创建对话框窗口
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProc);

	return 0;
}