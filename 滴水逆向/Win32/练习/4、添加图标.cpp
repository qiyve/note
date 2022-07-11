#include<stdio.h>
#include<Windows.h>
#include"resource.h"

HINSTANCE hAppInstance;

BOOL CALLBACK DialogProc(
	HWND hwndDlg,  // handle to dialog box			
	UINT uMsg,     // message			
	WPARAM wParam, // first message parameter			
	LPARAM lParam  // second message parameter			
)
{
	HWND hEditUser = NULL;
	HWND hEditPass = NULL;
	HICON hBigIcon;
	HICON hSmallIcon;

	switch (uMsg)
	{
	case WM_INITDIALOG:

	//加载图标          hAppInstance  应用程序句柄
	//MAKEINTRESOURCE 将整数值转换为与资源管理函数兼容的资源类型。此宏用于代替包含资源名称的字符串。
	hBigIcon = LoadIcon(hAppInstance, MAKEINTRESOURCE(IDI_ICON1)); //  IDI_ICON1 图标编号
	hSmallIcon = LoadIcon(hAppInstance, MAKEINTRESOURCE(IDI_ICON1));
	//设置图标
	SendMessage(hwndDlg, WM_SETICON, ICON_BIG, (DWORD)hBigIcon); // ICON_BIG 设置窗口的大图标。
	SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (DWORD)hSmallIcon);// ICON_SMALL 设置窗口的小图标。

		return TRUE;

	case  WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case   IDC_BUTTON_OK:

			//第一步，先获取文本框的句柄
			hEditUser = GetDlgItem(hwndDlg, IDD_DIALOG1);
			hEditPass = GetDlgItem(hwndDlg, IDD_DIALOG1);
			// 2、获取文本框内容
			TCHAR szUserBuff[0x50];
			TCHAR szPassBuffer[0x50];

			GetWindowText(hEditUser, szUserBuff, 0x50);
			GetWindowText(hEditPass, szPassBuffer, 0x50);

			MessageBox(NULL, TEXT("IDC_BUTTON_OK"), TEXT("OK"), MB_OK);

			return TRUE;

		case   IDC_BUTTON_ERROR:

			MessageBox(NULL, TEXT("IDC_BUTTON_ERROR"), TEXT("ERROR"), MB_OK);

			EndDialog(hwndDlg, 0);

			return TRUE;
		}
		break;
	}

	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	hAppInstance = hInstance;
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);

}
