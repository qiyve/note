#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include"resource.h"

HWND hEdit1;  //第一个对话框
HWND hEdit2;  //第二个对话框

DWORD WINAPI ThreadProc(
    LPVOID lpParameter   // thread data		
    )
{
   //创建内存
    CHAR szBuffer1[10];
    CHAR szBuffer2[10];
    memset(szBuffer1, 0, 10);
    memset(szBuffer2, 0, 10);
    //获取文本框内容
    GetWindowTextA(hEdit1, szBuffer1, 10);
    GetWindowTextA(hEdit2, szBuffer2, 10);

    // 分别存储第两个对话框的值
    DWORD dwTimer1,dwTimer2;
    //字符转成整形 
    sscanf(szBuffer1, "%d", &dwTimer1);
    sscanf(szBuffer2, "%d", &dwTimer2);

    while (dwTimer1 > 0 && dwTimer2 < 1000)
    {
        //重新初始化内存为 0 
        memset(szBuffer1, 0, 10);
        memset(szBuffer2, 0, 10);

        dwTimer1--, dwTimer2++;
      
        Sleep(10); //暂停执行的时间间隔，以毫秒为单位。

        // 数字转字符
        sprintf((char*)szBuffer1, "%d", dwTimer1);
        sprintf((char*)szBuffer2, "%d", dwTimer2);
        // 写回 文本框重新赋值
        SetWindowTextA(hEdit1, szBuffer1);
        SetWindowTextA(hEdit2, szBuffer2);

    }
   
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
            SetWindowTextA(hEdit1, LPCSTR("1000"));
            //获取第二个文本框  句柄
            hEdit2 = GetDlgItem(hDlg, IDC_EDIT2);
            SetWindowTextA(hEdit2, LPCSTR("0"));
             return TRUE;
        }
        
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON:
            {   
                //创建一个新的线程				
                HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc,
                NULL, 0, NULL);
               // 如果不在其他的地方引用它 关闭句柄	 不会影响线程			
               //::CloseHandle(hThread);
                
                return TRUE;
             }
        }
        break;
    }
    return Ret;
}

int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    PSTR      lpCmdLine,
                    int       nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, MainDlgProc);
}