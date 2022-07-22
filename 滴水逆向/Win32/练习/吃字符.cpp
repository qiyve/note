
#include <windows.h>
#include <stdio.h>  
#include <tchar.h>        // TCHAR  操作函数 头文件  
#include "resource.h"    

//文本框句柄
HWND hRes;
HWND hBuf[2];  //生产者
HWND hTxt[4];  //消费者

//临界区
CRITICAL_SECTION cs;

//信号量
HANDLE hSemaphoreCust;
HANDLE hSemaphoreProd;

//线程句柄
HANDLE hThread[5];

//生产者线程
DWORD WINAPI ThreadProcProd(LPVOID lpParameter)
{
    //读取资源
    TCHAR szBuffer[256];
    memset(szBuffer, 0, 256 * sizeof(TCHAR));
    ::GetWindowText(hRes, szBuffer, 256);

    //将字符写入到缓冲区
    DWORD len = _tcslen(szBuffer);    //获取字符串长度
    for (int i = 0; i < len; i++) 
    {
        ::WaitForSingleObject(hSemaphoreProd, INFINITE);    //等待生产者信号量

        EnterCriticalSection(&cs);   //获取令牌

        TCHAR szBuf[256];

        TCHAR szTmp[2];
        memset(szTmp, 0, 2 * sizeof(TCHAR));
        memcpy(szTmp, szBuffer + i, sizeof(TCHAR));    //字符拷贝到临时缓冲区
        for (int j = 0; j < 2; j++) {
            memset(szBuf, 0, 256 * sizeof(TCHAR));
            ::GetWindowText(hBuf[j], szBuf, 256 * sizeof(TCHAR));
            if (_tcscmp(szBuf, TEXT("0")) == 0) {    //如果有有一个缓冲区为0则添加
                ::SetWindowText(hBuf[j], szTmp);
                break;
            }
        }

        ::ReleaseSemaphore(hSemaphoreCust, 1, NULL);    //每次放完之后释放一个消费者信号量
        LeaveCriticalSection(&cs);
    }

    return 0;
}

//消费者线程
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    DWORD index = (DWORD)lpParameter;
    while (TRUE) {
        ::WaitForSingleObject(hSemaphoreCust, INFINITE);

        EnterCriticalSection(&cs);   //获取令牌

        //从缓冲区中读取字母
        TCHAR szTmp[2];
        memset(szTmp, 0, 2 * sizeof(TCHAR));
        for (int i = 0; i < 2; i++) {    //有两个缓冲区，其中一个不为0就从那里读
            ::GetWindowText(hBuf[i], szTmp, 2);
            if (_tcscmp(szTmp, TEXT("0")) != 0) {

                Sleep(1000);
                //写入自己的文本框
                TCHAR szBuffer[256];
                memset(szBuffer, 0, 256 * sizeof(TCHAR));
                ::GetWindowText(hTxt[index], szBuffer, 256);
                DWORD len = _tcslen(szBuffer);
                TCHAR buf[256];
                memset(buf, 0, 256 * sizeof(TCHAR));
                memcpy(buf, TEXT("_"), sizeof(TCHAR));
                memcpy(buf + 1, szTmp, sizeof(TCHAR));
                memcpy(buf + 2, szBuffer, len * sizeof(TCHAR));
                ::SetWindowText(hTxt[index], buf);

                //缓冲区置0
                ::SetWindowText(hBuf[i], TEXT("0"));
                Sleep(500);

                break;
            }
        }
        ::ReleaseSemaphore(hSemaphoreProd, 1, NULL);
        LeaveCriticalSection(&cs);
    }
    return 0;
}


//线程函数
DWORD WINAPI ThreadBegin(LPVOID lpParameter)
{
    hSemaphoreProd = CreateSemaphore(NULL, 2, 2, NULL);        //生产者信号量,初始有2个信号
    hSemaphoreCust = CreateSemaphore(NULL, 0, 2, NULL);        //消费者信号量

    InitializeCriticalSection(&cs);        //初始化临界区

    //开启消费者线程
    hThread[0] = ::CreateThread(NULL, 0, ThreadProc, (void*)0, 0, NULL);
    hThread[1] = ::CreateThread(NULL, 0, ThreadProc, (void*)1, 0, NULL);
    hThread[2] = ::CreateThread(NULL, 0, ThreadProc, (void*)2, 0, NULL);
    hThread[3] = ::CreateThread(NULL, 0, ThreadProc, (void*)3, 0, NULL);
    //开启生产者线程
    hThread[4] = ::CreateThread(NULL, 0, ThreadProcProd, NULL, 0, NULL);

    //释放信号量
    ::WaitForMultipleObjects(5, hThread, TRUE, INFINITE);            //当5个线程运行完后会自动进入已通知状态，此时关闭信号量
    ::CloseHandle(hSemaphoreProd);
    ::CloseHandle(hSemaphoreProd);
    return 0;
}

//回调函数            
BOOL CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL bRet = FALSE;
    switch (uMsg)
    {
    case WM_CLOSE:
    {
        EndDialog(hDlg, 0);
        break;
    }
    case WM_INITDIALOG:
    {
        //获取文本框句柄
        hRes = GetDlgItem(hDlg, IDC_EDIT_1);
        hBuf[0] = GetDlgItem(hDlg, IDC_EDIT_2);
        hBuf[1] = GetDlgItem(hDlg, IDC_EDIT_3);
        hTxt[0] = GetDlgItem(hDlg, IDC_EDIT_4);
        hTxt[1] = GetDlgItem(hDlg, IDC_EDIT_5);
        hTxt[2] = GetDlgItem(hDlg, IDC_EDIT_6);
        hTxt[3] = GetDlgItem(hDlg, IDC_EDIT_7);

        //初始化文本框
        ::SetWindowText(hRes, TEXT("0"));
        ::SetWindowText(hBuf[0], TEXT("0"));
        ::SetWindowText(hBuf[1], TEXT("0"));

        break;
    }
    case WM_COMMAND:

        switch (LOWORD(wParam))
        {
        case IDC_BUTTON:
        {
            ::CreateThread(NULL, 0, ThreadBegin, NULL, 0, NULL);
            return TRUE;
        }
        }
        break;
    }

    return bRet;
}


//入口函数             
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, MainDlgProc);
    return 0;
}