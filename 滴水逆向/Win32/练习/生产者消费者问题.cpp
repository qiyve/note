#include<windows.h>
#include<stdio.h>


//临界区方式
//CRITICAL_SECTION g_cs;
//int g_Max = 10;
//int g_Number = 0;
//int a = TRUE;
////生产者线程函数          
//DWORD WINAPI ThreadProduct(LPVOID pM)
//{
//    for (int i = 0; i < g_Max; i++)
//    {
//        //互斥的访问缓冲区          
//        EnterCriticalSection(&g_cs);
//        if (a == TRUE)
//        {
//            g_Number = 1;
//            DWORD id = GetCurrentThreadId();
//            printf("生产者%d将数据%d放入缓冲区\n", id, g_Number);
//            a = FALSE;
//        }
//        LeaveCriticalSection(&g_cs);
//
//        Sleep(1000);
//    }
//    return 0;
//}
////消费者线程函数        
//DWORD WINAPI ThreadConsumer(LPVOID pM)
//{
//    for (int i = 0; i < g_Max; i++)
//    {
//        //互斥的访问缓冲区          
//        EnterCriticalSection(&g_cs);
//        if (a == FALSE)
//        {
//            g_Number = 0;
//            DWORD id = GetCurrentThreadId();
//            printf("----消费者%d将数据%d放入缓冲区\n", id, g_Number);
//            a = TRUE;
//        }
//        LeaveCriticalSection(&g_cs);
//        Sleep(1000);
//
//    }
//    return 0;
//}
//
//int main(int argc, char* argv[])
//{
//    InitializeCriticalSection(&g_cs);
//    HANDLE hThread[2];
//
//    hThread[0] = ::CreateThread(NULL, 0, ThreadProduct, NULL, 0, NULL);
//    hThread[1] = ::CreateThread(NULL, 0, ThreadConsumer, NULL, 0, NULL);
//
//    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
//    CloseHandle(hThread[0]);
//    CloseHandle(hThread[1]);
//
//    //销毁     
//    DeleteCriticalSection(&g_cs);
//    return 0;
//}


//事件方式
HANDLE g_hSet, g_hClear;
int g_Max = 10;
int g_Number = 0;

//生产者线程函数          
DWORD WINAPI ThreadProduct(LPVOID pM)
{
    for (int i = 0; i < g_Max; i++)
    {
        WaitForSingleObject(g_hSet, INFINITE);
        g_Number = 1;
        DWORD id = GetCurrentThreadId();
        printf("生产者%d将数据%d放入缓冲区\n", id, g_Number);
        SetEvent(g_hClear);
    }
    return 0;
}
//消费者线程函数        
DWORD WINAPI ThreadConsumer(LPVOID pM)
{
    for (int i = 0; i < g_Max; i++)
    {
        WaitForSingleObject(g_hClear, INFINITE);
        g_Number = 0;
        DWORD id = GetCurrentThreadId();
        printf("----消费者%d将数据%d放入缓冲区\n", id, g_Number);
        SetEvent(g_hSet);
    }
    return 0;
}

int main(int argc, char* argv[])
{

    HANDLE hThread[2];

    g_hSet = CreateEvent(NULL, FALSE, TRUE, NULL);
    g_hClear = CreateEvent(NULL, FALSE, FALSE, NULL);

    hThread[0] = ::CreateThread(NULL, 0, ThreadProduct, NULL, 0, NULL);
    hThread[1] = ::CreateThread(NULL, 0, ThreadConsumer, NULL, 0, NULL);

    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
    CloseHandle(hThread[0]);
    CloseHandle(hThread[1]);

    //销毁     
    CloseHandle(g_hSet);
    CloseHandle(g_hClear);

    return 0;
}