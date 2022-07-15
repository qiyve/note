#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include"resource.h"


HWND  hEdit1;
HANDLE hThread;
int x = 0;

DWORD WINAPI ThreadProc( LPVOID lpParameter ) // thread data
{
    CHAR szBuffer[10];
    DWORD dwIndex = 0;
    DWORD dwCount;

    while (dwIndex < 100)
    {
        // 第一种 该方式会连同该线程的堆栈一起释放掉
       // ::ExitThread(1); 参数为指定线程的退出码，可以通过GetExitCodeThread 来查看
      /*   if (dwIndex == 30)
        {
            ::ExitThread(0);
        }*/

        //第二种 2.线程函数返回  最优
    /*    if (x == 1)
        {
            break;
        }*/

        GetWindowTextA(hEdit1, (LPSTR)szBuffer, 10);
        sscanf(szBuffer, "%d", &dwCount);
        dwCount++;
        Sleep(200);
        memset(szBuffer, 0, 10);
        sprintf(szBuffer, "%d", dwCount);
        SetWindowTextA(hEdit1, (LPCSTR)szBuffer);
        dwIndex++;
    }
    // 2.写自己用来释放资源的代码....

    return 0;
}
//消息处理
BOOL CALLBACK MainDlgProc(
    HWND hDlg,  //对话框句柄
    UINT uMsg,     //消息 message
    WPARAM wParam, //第一个消息参数 第一个消息参数
    LPARAM lParam
)
{
    DWORD Ret = FALSE;
    switch (uMsg)
    {
    case WM_CLOSE:
    {
        EndDialog(hDlg, 0);
        break;
    }
    case WM_INITDIALOG:
    {
        //获取当前文本框 句柄
        hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
        SetWindowTextA(hEdit1, LPCSTR("0"));
        return TRUE;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
        {
            //创建一个新的线程				
            hThread = ::CreateThread(NULL, 0, ThreadProc,
                NULL, 0, NULL);
            // 如果不在其他的地方引用它 关闭句柄	 不会影响线程			
            //::CloseHandle(hThread);
            return TRUE;
        }
        case IDC_BUTTON2:  //挂起
        {
            ::SuspendThread(hThread); //参数 需要挂起的线程句柄
            return TRUE;
        }
        case IDC_BUTTON3: //恢复
        {
            ::ResumeThread(hThread);
            return TRUE;
        }
        case IDC_BUTTON4: //终止
        {
            //第三种  异步 
            ::TerminateThread(hThread, 2);
            ::WaitForSingleObject(hThread, INFINITE); //等待指定的对象处于信号状态或超时间隔过去。
            return TRUE;
        }
        break;
        }
    }
    return Ret;
}

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR      lpCmdLine,
    int       nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, MainDlgProc);
}