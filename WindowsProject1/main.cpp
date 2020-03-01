// main.cpp
// HP Editor application file

// *** plans TODO: ***
// 09.02.20
// - [09.02.20] draw Grid (main level0 grid)
// - [09.02.20] load Grid from file.xml
// - [09.02.20] [16.02.20] find a concept to separate graphic engine from Wast-project core logic
// - [09.02.20] save Grid to file.xml
// + [23.02.20] [01.03.20] place Wast Grid logic here
// - [01.03.20] place CMD "new" with empty wast file in dialog
// - [01.03.20] prepare function for CMD "new" with empty HPGrid and support
// - [01.03.20] complete nodes OPs in "hhexlogic"



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
	// new main Dialog instance
	PKDialog mainDlg(hInstance, IDD_DIALOG_MAIN, HWND_DESKTOP);

	// show main dialog
	mainDlg.DoModal();

	
	return 0;
}
