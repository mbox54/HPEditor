// main.cpp
// HP Editor application file

////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////
#include "project.h"
#include "pkdialog.h"


////////////////////////////////////////////////////////////
// function
////////////////////////////////////////////////////////////

//BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	static char m_edText[256] = "";
//
//	switch (msg)
//	{
//	case WM_INITDIALOG:
//		oldEditProc = (WNDPROC)SetWindowLongPtr(
//			GetDlgItem(hDlg, IDC_EDIT_CMD),
//			GWLP_WNDPROC, (LONG)newEditProc);
//		break;
//
//
//	case WM_COMMAND:
//		if (wParam == IDCANCEL)
//			EndDialog(hDlg, 0);
//
//		//if (wParam == IDC_BUTTON1)
//		//{
//		//	int msgboxID = MessageBox(hDlg, "x1", "x2", MB_OK);
//
//		//	switch (msgboxID)
//		//	{
//		//	case IDCANCEL:
//		//		// TODO: add code
//		//		break;
//		//	case IDOK:
//		//		// TODO: add code
//		//		break;
//		//	}
//		//}
//
//		break;
//
//
//	case WM_KEYDOWN:
//		if (VK_RETURN == wParam)
//			GetDlgItemText(hDlg, IDC_EDIT_CMD, (LPWSTR) m_edText, 256);
//		break;
//
//	}
//
//	return 0;
//}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// new main Dialog object
	PKDialog mainDlg(hInstance, IDD_DIALOG_MAIN, HWND_DESKTOP);

	// show main dialog
	mainDlg.DoModal();

	
	return 0;
}
