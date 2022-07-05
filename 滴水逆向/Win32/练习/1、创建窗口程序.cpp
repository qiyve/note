#include<stdio.h>
#include<Windows.h>

/*
步骤1：创建Windows应用程序  选择空项目
步骤2：在新建项窗口中选C++代码文件 创建一个新的cpp文件
步骤3：在新的cpp文件中添加:#include <Windows.h>
并添加入口函数：
*/

HINSTANCE hAppInstance;

LRESULT CALLBACK WindowProc(
	IN  HWND hwnd,
	IN  UINT uMsg,
	IN  WPARAM wParam,
	IN  LPARAM lParam
);


int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,			//应用程序的当前实例的句柄
	_In_  HINSTANCE hPrevInstance,		//应用程序上一个实例的句柄
	_In_  LPSTR lpCmdLine,				//应用程序的命令行
	_In_  int nCmdShow					//控制窗口的显示方式
)  										//CALLBACK 是一个宏
{										//#define CALLBACK    __stdcall
										//所有的Win32     API函数都遵循该约定
	//步骤4：设计窗口类
	TCHAR className[] = TEXT("My First Window");

	//创建窗口类的对象
	WNDCLASS wndclass = { 0 };						//一定要先将所有值赋值
	wndclass.hbrBackground = (HBRUSH)COLOR_MENU;	//窗口的背景色
	wndclass.lpfnWndProc = WindowProc;				//窗口过程函数
	wndclass.lpszClassName = className;				//窗口类的名字	
	wndclass.hInstance = hInstance;					//定义窗口类的应用程序的实例句柄			

	//步骤5：注册窗口类
	RegisterClass(&wndclass);
	//步骤6：创建窗口
	// 创建窗口  							
	HWND hwnd = CreateWindow(
		className,					//类名		
		TEXT("我的第一个窗口"),		//窗口标题		
		WS_OVERLAPPEDWINDOW,		//窗口外观样式 		
		10,							//相对于父窗口的X坐标		
		10,							//相对于父窗口的Y坐标		
		600,						//窗口的宽度  		
		300,						//窗口的高度  		
		NULL,						//父窗口句柄，为NULL  		
		NULL,						//菜单句柄，为NULL  		
		hInstance,					//当前应用程序的句柄  		
		NULL);						//附加数据一般为NULL		

	if (hwnd == NULL)				//是否创建成功  		
		return 0;

	//步骤7：显示窗口
	ShowWindow(hwnd, SW_SHOW);
	//步骤8：消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		/*功能：将虚拟键消息转换成字符信息，字符信息被送到调用线程的消息队列中，
		在下一次线程调用函数GetMessage或PeekMessages时被读取*/
		TranslateMessage(&msg);

	//该函数调度一个信息给窗口程序，通常调度从GetMessage取得的消息。消息被调度到的窗口程序即是MainProc()函数
		DispatchMessage(&msg);
	}

	return 0;
}

//步骤9：回调函数
/*
   窗口消息处理程序 窗口回调函数：
1、窗口回调函数处理过的消息，必须传回0.
2、窗口回调不处理的消息，由DefWindowProc来处理.
*/

LRESULT CALLBACK WindowProc(
	IN HWND hwnd,
	IN UINT uMsg,
	IN WPARAM wParam,
	IN LPARAM lParam
)
{   
	switch (uMsg)
	{
	case WM_DESTROY:
	//函数功能描述:PostQuitMessage函数通知系统当前有一个线程发送了进程中止退出请求.它典型的使用在WM_DESTROY消息处理中
		PostQuitMessage(0);
	}
	//默认的窗口处理函数 我们可以把不关心的消息都丢给它来处理
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}