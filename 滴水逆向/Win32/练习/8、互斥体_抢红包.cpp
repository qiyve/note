#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include"resource.h"


//创建文本对话框句柄
HWND hongbao;  //IDC_EDIT_1  存储红包数量对话框
HWND zg;  //IDC_EDIT_2   抢红包线程1
HWND wst;  //IDC_EDIT_3  抢红包线程2
HWND smy;  //IDC_EDIT_4  抢红包线程3

//创建
HANDLE g_hMutex;
DWORD num;   //红包值


//  zg 
DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	while (num > 0)
	{
		//等待互斥体   INFINITE -1 表示一直等待
		WaitForSingleObject(g_hMutex, INFINITE);
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
		//释放互斥体
		ReleaseMutex(g_hMutex);
		Sleep(1000);
	}
	return 0;
}

//wst
DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	while (num > 0)
	{
		//等待互斥体   INFINITE -1 表示一直等待
		WaitForSingleObject(g_hMutex, INFINITE);
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
		//释放互斥体
		ReleaseMutex(g_hMutex);
		Sleep(1000);
	}
	return 0;
}

//smy
DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	while (num > 0)
	{
		//等待互斥体   INFINITE -1 表示一直等待
		WaitForSingleObject(g_hMutex, INFINITE);
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
		//释放互斥体
		ReleaseMutex(g_hMutex);
		Sleep(1000);
	}
	return 0;
}

//线程函数
DWORD WINAPI ThreadProc(
	LPVOID lpParameter  //给线程传递参数
)
{
	//创建互斥体
	g_hMutex = CreateMutex(NULL, FALSE, (LPCWSTR)"XYZ");
	//创建内核对象数组
	HANDLE hArray[3];

	//创建线程
	HANDLE hThread1 = ::CreateThread(NULL, 0, ThreadProc1, NULL, 0, NULL);
	HANDLE hThread2 = ::CreateThread(NULL, 0, ThreadProc2, NULL, 0, NULL);
	HANDLE hThread3 = ::CreateThread(NULL, 0, ThreadProc3, NULL, 0, NULL);

	hArray[0] = hThread1;
	hArray[1] = hThread2;
	hArray[2] = hThread3;

	//等待所有线程执行完毕后关闭互斥体
	//参数1: 要查看内核对象数量. 参数：内核对象数组。参数3 	等到类型  TRUE 等到所有变为已通知  FALSE 只要有一个变为已通知
	DWORD dwCode = ::WaitForMultipleObjects(3, hArray, FALSE, INFINITE);
	::CloseHandle(g_hMutex);

	return 0;
}

//回调函数
BOOL CALLBACK DialogProc(
			HWND	hwndDlg, // handle to dialog box
			UINT	uMsg,	 // message   
			WPARAM	wParam,	 // first message parameter 
			LPARAM	lParam	 // second message parameter   
)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			//获取显示红包值 文本对话框的句柄
			hongbao = GetDlgItem(hwndDlg, IDC_EDIT_1);
		    //获取其他句柄
			zg = GetDlgItem(hwndDlg, IDC_EDIT_2);
			wst = GetDlgItem(hwndDlg, IDC_EDIT_3);
			smy = GetDlgItem(hwndDlg, IDC_EDIT_4);

			//初始化文本兑换的值
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
				//获取文本框内容
				CHAR szBuffer[10];
				memset(szBuffer, 0, 10);
				GetWindowTextA(hongbao, szBuffer, 10);
				//字符串转数字
				sscanf(szBuffer, "%d", &num);

				//清空输入框
				SetWindowText(zg, TEXT("0"));
				SetWindowText(wst, TEXT("0"));
				SetWindowText(smy, TEXT("0"));

				//创建线程
				HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
				//如果不在其它的地方引用它 关闭句柄
				::CloseHandle(hThread);
				return TRUE;
			}
			return FALSE;
		}
		break;
	case WM_CLOSE: //退出功能
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

}