#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include"resource.h"


HANDLE hSemaphore;	//创建信号量句柄 信号量也是内核对象
HANDLE hThread[3];  //创建内核数组

//创建句柄
HWND hEditSet;
HWND hEdit1;
HWND hEdit2;
HWND hEdit3;


DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	CHAR szBuffer[10];
	DWORD dwNum = 0;

	//等待
	WaitForSingleObject(hSemaphore, INFINITE);
	while (dwNum < 100)
	{
		Sleep(100);
		memset(szBuffer, 0, 10);
		GetWindowTextA(hEdit1, szBuffer, 10); //获取文本框的值
		sscanf(szBuffer, "%d", &dwNum);       //字符转整形
		dwNum++;
		memset(szBuffer, 0, 10);
		sprintf(szBuffer, "%d", dwNum);		 //数字转字符
		SetWindowTextA(hEdit1, szBuffer);	 //写回文本框
	}
	ReleaseSemaphore(hSemaphore, 1, NULL);
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	CHAR szBuffer[10];
	DWORD dwNum = 0;

	//等待
	WaitForSingleObject(hSemaphore, INFINITE);
	while (dwNum < 100)
	{
		Sleep(100);
		memset(szBuffer, 0, 10);
		GetWindowTextA(hEdit2, szBuffer, 10); //获取文本框的值
		sscanf(szBuffer, "%d", &dwNum);       //字符转整形
		dwNum++;
		memset(szBuffer, 0, 10);
		sprintf(szBuffer, "%d", dwNum);		 //数字转字符
		SetWindowTextA(hEdit2, szBuffer);	 //写回文本框
	}
	ReleaseSemaphore(hSemaphore, 1, NULL);
	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	CHAR szBuffer[10];
	DWORD dwNum = 0;

	//等待
	WaitForSingleObject(hSemaphore, INFINITE);
	while (dwNum < 100)
	{
		Sleep(100);
		memset(szBuffer, 0, 10);
		GetWindowTextA(hEdit3, szBuffer, 10); //获取文本框的值
		sscanf(szBuffer, "%d", &dwNum);       //字符转整形
		dwNum++;
		memset(szBuffer, 0, 10);
		sprintf(szBuffer, "%d", dwNum);		 //数字转字符
		SetWindowTextA(hEdit3, szBuffer);	 //写回文本框
	}
	ReleaseSemaphore(hSemaphore, 1, NULL);
	return 0;
}

// 线程函数 
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	CHAR szBuffer[10];
	DWORD dwNum = 0;

	//创建信号量
	// 1. 安全控制  2.初始化资源数量 为0时不发送信号 3.最大并发数量 4.表示信号量的名称 NULL表示匿名信号量
	hSemaphore = CreateSemaphore(NULL, 0, 3, NULL);

	//创建线程
	hThread[0] = ::CreateThread(NULL, 0, ThreadProc1, NULL, 0, NULL);
	hThread[1] = ::CreateThread(NULL, 0, ThreadProc2, NULL, 0, NULL);
	hThread[2] = ::CreateThread(NULL, 0, ThreadProc3, NULL, 0, NULL);

	//
	while (dwNum < 1000)
	{
		memset(szBuffer, 0, 10);
		GetWindowTextA(hEditSet, szBuffer, 10);
		sscanf(szBuffer, "%d", &dwNum);
		dwNum++;
		memset(szBuffer, 0, 10);
		sprintf(szBuffer, "%d", dwNum);
		SetWindowTextA(hEditSet, szBuffer);
	}
	ReleaseSemaphore(hSemaphore, 2, NULL); //发送2个信号量，可以是等待hSemaphore的两个线程开始运行

	::WaitForMultipleObjects(3, hThread, TRUE, INFINITE);//当3个线程运行完后自动进入已通知状态，此时关闭信号量
	::CloseHandle(hSemaphore);

	return 0;
}

//回调函数
BOOL CALLBACK MainDlgProc(
		HWND	hDlg,
		UINT	uMsg,
		WPARAM wParam,
		LPARAM lParam
	)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		{
			EndDialog(hDlg, 0);
			return TRUE;
		}
	case WM_INITDIALOG:
		{
			//获取句柄
			hEditSet = GetDlgItem(hDlg, IDC_EDIT1);
			hEdit1 = GetDlgItem(hDlg, IDC_EDIT2);
			hEdit2 = GetDlgItem(hDlg, IDC_EDIT3);
			hEdit3 = GetDlgItem(hDlg, IDC_EDIT4);

			//初始化文本为0
			SetWindowText(hEditSet, TEXT("0"));
			SetWindowText(hEdit1, TEXT("0"));
			SetWindowText(hEdit2, TEXT("0"));
			SetWindowText(hEdit3, TEXT("0"));

			break;
		}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			{
				////额外创建一个线程来控制其他线程，防止主线程阻塞
				CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

int APIENTRY WinMain( HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR		lpComLine,
					  int		nCmdShow

)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainDlgProc);
	return 0;
}

