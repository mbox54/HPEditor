// pkdialog.cpp: implementation of the PKDialog class.
//
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////
#include "project.h"
#include "pkdialog.h"


////////////////////////////////////////////////////////////
// *** support classes ***
////////////////////////////////////////////////////////////
// Edit-'COMMAND'

////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////
// static section
long Edit_cmd::m_lThis = 0;

Edit_cmd::Edit_cmd()
{
	m_hMainDlgProcHandle = NULL;

	// store handler to this
	Edit_cmd::m_lThis = (long)this;
}


Edit_cmd::~Edit_cmd()
{
	// pointed to null
	Edit_cmd::m_lThis = 0;
}


////////////////////////////////////////////////////////////
// methods
////////////////////////////////////////////////////////////

// NOTE:
// static procedure must be called after Object is constructed!
LRESULT CALLBACK Edit_cmd::EditProcStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// NOTE:
	// call proc as class method
	Edit_cmd* pThis = (Edit_cmd*)Edit_cmd::m_lThis;

	return (pThis->EditProc(hWnd, msg, wParam, lParam));
}


// edit-'COMMAND' control message routine
LRESULT Edit_cmd::EditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_KEYDOWN:
		if (VK_RETURN == wParam)
		{
			SendMessage(m_hWndParent, msg, wParam, lParam);
			SetFocus(GetNextDlgTabItem(m_hWndParent, hWnd, FALSE));

			return 0;
		}
		break;


	case WM_CHAR:
		if (VK_RETURN == wParam)
			return 0;

		break;
	}

	return CallWindowProc(*m_hMainDlgProcHandle, hWnd, msg, wParam, lParam);
}


void Edit_cmd::Init(int nResId, HWND hWndParent, WNDPROC* hMainDlgProcHandle)
{
	// copy properties to item
	m_nResId = nResId;
	m_hWndParent = hWndParent;
	m_hMainDlgProcHandle = hMainDlgProcHandle;

	// replace main message proc to edit-'COMMAND' control
	// save main dlg proc handle to use it for next call in proc sequence
	HWND m_hEdit = GetDlgItem(m_hWndParent, m_nResId);

	*m_hMainDlgProcHandle = (WNDPROC)SetWindowLongPtr(
		m_hEdit,
		GWLP_WNDPROC,
		(LONG)EditProcStatic);
}


////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////
// static section
HWND PKDialog::m_hWindow = NULL;
long PKDialog::m_lThis = 0;

// common
PKDialog::PKDialog(HINSTANCE hInstance, int nResId, HWND hWndParent) :
	m_hInstance(hInstance),
	m_nResId(nResId),
	m_hWndParent(hWndParent)
{
	// store handler to this
	PKDialog::m_lThis = (long)this;

	// handle variable, init NULL here
	m_hMainDlgProcHandle = NULL;
	m_hProcHandle = NULL;
}


PKDialog::~PKDialog()
{
	// free mem
	PKDialog::m_hWindow = NULL;

	// pointed to null
	PKDialog::m_lThis = 0;
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

	PKDialog* pThis = (PKDialog*)PKDialog::m_lThis;

	return (pThis->DlgProc(hDlg, msg, wParam, lParam));
}


////////////////////////////////////////////////////////////
// class methods
////////////////////////////////////////////////////////////
void PKDialog::Init(HWND hDlg)
{
	// save control handles here
	// NOTE:
	// they've already need to be used here in proc_handle

	// > Controls
	// Edit-'COMMAND'
	m_Edit_cmd.Init(IDC_EDIT_CMD, hDlg, &m_hMainDlgProcHandle);

}

// main dialog message routine
BOOL PKDialog::DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static char m_edText[256] = "";

	switch (msg)
	{
	case WM_INITDIALOG:

		Init(hDlg);

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


// create dialog
// NOTE:
// upon this proc property 'm_hWindow' is filled
// main dlg message routine srartes here
void PKDialog::DoModal(void)
{
	// show main dialog, start message proc
	DialogBox(m_hInstance, MAKEINTRESOURCE(m_nResId), HWND_DESKTOP, (DLGPROC)PKDialog::DlgProcStatic);
}
