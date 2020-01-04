// pkdialog.cpp: implementation of the PKDialog class.
//
//////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////
#include "project.h"
#include "pkdialog.h"


////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////
// static section
HWND PKDialog::m_hWindow = NULL;
HWND PKDialog::m_hEdit = NULL;
long PKDialog::m_lSaveThis = 0;

// common
PKDialog::PKDialog(HINSTANCE hInstance, int nResId, HWND hWndParent) :
	m_hInstance(hInstance),
	m_nResId(nResId),
	m_hWndParent(hWndParent)
{
	// store handler to this
	m_lSaveThis = (long)this;
}


PKDialog::~PKDialog()
{
	// free mem
	PKDialog::m_hWindow = NULL;
	PKDialog::m_hEdit = NULL;

	// pointed to nothing
	PKDialog::m_lSaveThis = 0;
}


// static section
// NOTE:
// static procedure must be called after Object is constructed!
// (so DlgProc must existed)
BOOL CALLBACK PKDialog::DlgProcStatic(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// save Dlg window object handle
	if (m_hWindow == NULL)
	{
		PKDialog::m_hWindow = hDlg;
	}

	PKDialog* pThis = (PKDialog*)PKDialog::m_lSaveThis;

	return (pThis->DlgProc(hDlg, msg, wParam, lParam));
}

// NOTE:
// static procedure must be called after Object is constructed!
LRESULT CALLBACK PKDialog::EditProcStatic(HWND hEdit, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// save Edit window object handle
	if (m_hWindow == NULL)
	{
		PKDialog::m_hEdit = hEdit;
	}

	PKDialog* pThis = (PKDialog*)PKDialog::m_lSaveThis;

	return (pThis->EditProc(hEdit, msg, wParam, lParam));
}


////////////////////////////////////////////////////////////////////////////////
// class methods
////////////////////////////////////////////////////////////////////////////////
void PKDialog::Init(void)
{

}

BOOL PKDialog::DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static char m_edText[256] = "";

	switch (msg)
	{
	case WM_INITDIALOG:

		// save nain proc handle to use it for restoring proc event sequence
		m_hMainProcHandle = (WNDPROC)SetWindowLongPtr(
			GetDlgItem(hDlg, IDC_EDIT_CMD),
			GWLP_WNDPROC, (LONG)EditProcStatic);

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


		//case WM_KEYDOWN:
		//	if (VK_RETURN == wParam)
		//		GetDlgItemText(hDlg, IDC_EDIT_CMD, (LPWSTR)m_edText, 256);
		//	break;

	}

	return 0;
}

LRESULT PKDialog::EditProc(HWND hEdit, UINT msg, WPARAM wParam, LPARAM lParam)
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

	return CallWindowProc(m_hMainProcHandle, hEdit, msg, wParam, lParam);
}

// create dialog
void PKDialog::DoModal(void)
{
	// show main dialog, start message proc
	DialogBox(m_hInstance, MAKEINTRESOURCE(m_nResId), HWND_DESKTOP, (DLGPROC)PKDialog::DlgProcStatic);
}
