#include<windows.h>
#include<stdio.h>
#include "resource.h"

HANDLE g_hEvent; // 事件
// 文本对话框句柄
HWND hEdit1;
HWND hEdit2;
HWND hEdit3;
HWND hEdit4;

DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	TCHAR szBuffer[10] = { 0 };//初始化为0

	//等待事件变成已通知时
	WaitForSingleObject(g_hEvent, INFINITE); // INFINITE:  -1  表示一直等待
	//读取内容
	GetWindowText(hEdit1, szBuffer, 10);
	SetWindowText(hEdit2, szBuffer); //写回  hEdit2 文本框中
	Sleep(1000);
	//设置事件为已通知状态
	//SetEvent(g_hEvent);
	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	TCHAR szBuffer[10] = { 0 };

	//等待事件变为已通知状态
	WaitForSingleObject(g_hEvent, -1);
	//读取第一个文本框的值  写回到 3 文本框
	GetWindowText(hEdit1, szBuffer, 10);
	SetWindowText(hEdit3, szBuffer);

	Sleep(1000);
	//设置事件为已通知状态
	//SetEvent(g_hEvent);
	return 0;
}

DWORD WINAPI ThreadProc4(LPVOID lpParameter)
{
	TCHAR szBuffer[10] = { 0 };

	//等待事件变为已通知状态
	WaitForSingleObject(g_hEvent, -1);
	//读取第一个文本框的值  写回到 4 文本框
	GetWindowText(hEdit1, szBuffer, 10);
	SetWindowText(hEdit4, szBuffer);

	Sleep(1000);
	//设置事件为已通知状态
	//SetEvent(g_hEvent);
	return 0;
}

//线程函数 创建线程
DWORD WINAPI ThreadProc_1(LPVOID lpParameter)
{
	//创建事件
	//1：默认安全属性   2：(TRUE) 需要手动设置为未通知状态  FLASE：只要有线程wait到了该事件，立马会将该事件的状态改回去变成未通知状态
	//3：初始状态未通知  4名称
	g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	HANDLE hThread[3];
	//创建3个线程
	hThread[0] = CreateThread(NULL, 0, ThreadProc2, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, ThreadProc3, NULL, 0, NULL);
	hThread[2] = CreateThread(NULL, 0, ThreadProc4, NULL, 0, NULL);

	//设置文本框的值
	SetWindowText(hEdit1, TEXT("1000"));

	//设置事件为已通知状态
	SetEvent(g_hEvent);
	//等待线程结束 销毁内核对象
	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);
	CloseHandle(g_hEvent);

	return 0;
}

//回调函数
BOOL CALLBACK DialogProc(
			HWND	 hwndDlg,
			UINT	 uMsg,
			WPARAM   wParam,
			LPARAM   lParam
)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			hEdit1 = GetDlgItem(hwndDlg, IDC_EDIT_1);
			hEdit2 = GetDlgItem(hwndDlg, IDC_EDIT_2);
			hEdit3 = GetDlgItem(hwndDlg, IDC_EDIT_3);
			hEdit4 = GetDlgItem(hwndDlg, IDC_EDIT_4);
			return TRUE;
		}
			
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
			{	
				//额外创建一个线程来控制其他线程，防止主线程阻塞
				HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc_1, NULL, 0, NULL);
				//如果不在其他的地方引用它 关闭句柄
				::CloseHandle(hThread);
				return TRUE;
			}
			return FALSE;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		return TRUE;
	}

	return FALSE;
}

int CALLBACK WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevHinstance,
					 LPSTR	   lpCmdLine,
					 int       nCmdShow)
{
	//创建对话框窗口
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}