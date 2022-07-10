#include<stdio.h>
#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DialogProc(
	HWND hwndDlg,  // handle to dialog box			
	UINT uMsg,     // message			
	WPARAM wParam, // first message parameter			
	LPARAM lParam  // second message parameter			
)
{

	switch (uMsg)
	{
	case  WM_INITDIALOG:

		MessageBox(NULL, TEXT("WM_INITDIALOG"), TEXT("INIT"), MB_OK);

		return TRUE;

	case  WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case   IDC_BUTTON_OK:

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

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}