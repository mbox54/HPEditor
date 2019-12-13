#include <windows.h>
#include "resource.h"

WNDPROC oldEditProc = NULL;

LRESULT CALLBACK newEditProc(HWND hEdit, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		if (VK_RETURN == wParam)
		{
			HWND hParent = GetParent(hEdit);
			SendMessage(hParent, msg, wParam, lParam);
			SetFocus(GetNextDlgTabItem(hParent, hEdit, FALSE));
			return 0;
		}
	}
	break;

	case WM_CHAR:
		if (VK_RETURN == wParam)
			return 0;
		break;
	}
	return CallWindowProc(oldEditProc, hEdit, msg, wParam, lParam);
}


BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static char m_edText[256] = "";

	switch (msg)
	{
	case WM_INITDIALOG:
		oldEditProc = (WNDPROC)SetWindowLong(
			GetDlgItem(hDlg, IDC_EDIT1),
			GWL_WNDPROC, (LONG)newEditProc);
		break;


	case WM_COMMAND:
		if (wParam == IDCANCEL)
			EndDialog(hDlg, 0);

		//if (wParam == IDC_BUTTON1)
		//{
		//	int msgboxID = MessageBox(hDlg, "x1", "x2", MB_OK);

		//	switch (msgboxID)
		//	{
		//	case IDCANCEL:
		//		// TODO: add code
		//		break;
		//	case IDOK:
		//		// TODO: add code
		//		break;
		//	}
		//}

		break;


	case WM_KEYDOWN:
		if (VK_RETURN == wParam)
			GetDlgItemText(hDlg, IDC_EDIT1, (LPWSTR) m_edText, 256);
		break;

	}

	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, (DLGPROC)DlgProc);
	return 0;
}
