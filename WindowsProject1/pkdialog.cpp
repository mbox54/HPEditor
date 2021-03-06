// pkdialog.cpp: implementation of the PKDialog class.
// 
// PKDialog is stadalone class, singleton
// - incorporate all specific controls, that dialog needs 
// - has poiner variables and a way to perform subclassing 
//   calling all controls window procedures
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////
#include "project.h"
#include "pkdialog.h"

WNDPROC		m_hPreviousProcHandle;
////////////////////////////////////////////////////////////
// *** support classes ***
////////////////////////////////////////////////////////////
// > Common control prototype
////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////
// static section
long PKControl::m_lThis = 0;

PKControl::PKControl()
{
	m_hPreviousProcHandle = NULL;

	// store handler to this
	PKControl::m_lThis = (long)this;
}


PKControl::~PKControl()
{
	PKControl::m_lThis = 0;
}

// virtual
LRESULT PKControl::Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}


// > Edit-'COMMAND'
////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////
// static section
long Edit_cmd::m_lThis = 0;

Edit_cmd::Edit_cmd()
{
	m_hPreviousProcHandle = NULL;

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
LRESULT CALLBACK Edit_cmd::ProcStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// NOTE:
	// call proc as class method
	Edit_cmd* pThis = (Edit_cmd*)Edit_cmd::m_lThis;

	return (pThis->Proc(hWnd, msg, wParam, lParam));
}


// edit-'COMMAND' control message routine
LRESULT Edit_cmd::Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

	return CallWindowProc(*m_hPreviousProcHandle, hWnd, msg, wParam, lParam);
}


void Edit_cmd::Init(int nResId, HWND hWndParent, WNDPROC* hMainDlgProcHandle)
{
	// copy properties to item
	m_nResId = nResId;
	m_hWndParent = hWndParent;
	m_hPreviousProcHandle = hMainDlgProcHandle;

	// replace main message proc to edit-'COMMAND' control
	// save proc handle to use it for next call in proc sequence
	HWND m_hEdit = GetDlgItem(m_hWndParent, m_nResId);

	*m_hPreviousProcHandle = (WNDPROC)SetWindowLongPtr(
		m_hEdit,
		GWLP_WNDPROC,
		(LONG)ProcStatic);
}


// Canvas control
// static section
long Canvas::m_lThis = 0;

Canvas::Canvas()
{
	// store handler to this
	Canvas::m_lThis = (long)this;
}


Canvas::~Canvas()
{
	// pointed to null
	Canvas::m_lThis = NULL;
}


void Canvas::Init(int nResId, HWND hWndParent, WNDPROC* hProcHandle)
{
	// copy properties to item
	m_nResId = nResId;
	m_hWndParent = hWndParent;
	m_hPreviousProcHandle = hProcHandle;

	// replace message proc to edit-'COMMAND' control
	// save main dlg proc handle to use it for next call in proc sequence
	HWND m_hCanvas = GetDlgItem(m_hWndParent, m_nResId);

	*m_hPreviousProcHandle = (WNDPROC)SetWindowLongPtr(
		m_hCanvas,
		GWLP_WNDPROC,
		(LONG)ProcStatic);
}

// enter event proc
LRESULT Canvas::ProcStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Canvas* pThis = (Canvas*)Canvas::m_lThis;

	return (pThis->Proc(hWnd, msg, wParam, lParam));
}


LRESULT Canvas::Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// set hWnd
	if (m_hWnd == NULL)
	{
		m_hWnd = hWnd;

		// get wnd parameters
		InitCanvas();
	}
	
	// msg proc
	switch (msg)
	{

		//case WM_KEYDOWN:
		//	if (VK_RETURN == wParam)
		//		GetDlgItemText(hDlg, IDC_EDIT_CMD, (LPWSTR)m_edText, 256);
		//	break;


	case WM_PAINT:
		OnPaint();

		break;

	}

	// call parent events proc
	return CallWindowProc(*m_hPreviousProcHandle, hWnd, msg, wParam, lParam);
}


void Canvas::InitCanvas()
{
	// init Canvas object
	m_Draw.Init(m_hWnd);
}


void Canvas::OnPaint()
{
	// test
	m_Draw.Draw();
}

// Main Dialog section

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
	m_hEditCmd_ProcHandle = NULL;
	m_hCanvas_ProcHandle = NULL;

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
	m_Edit_cmd.Init(IDC_EDIT_CMD, hDlg, &m_hEditCmd_ProcHandle);

	// Picture-'Canvas'
	m_Canvas.Init(IDC_STATIC_CANVAS, hDlg, &m_hCanvas_ProcHandle);

	// *** work object ***
	// give Grid-logic to Draw-library
	m_Canvas.m_Draw.SetGridObject(&m_HPGrid);

	// prerare new work
	FileNew();

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
		// *** main OPs ***
		// exit programm
		if (wParam == IDCANCEL)
		{
			EndDialog(hDlg, 0);
		}

		// about dialog
		if (wParam == IDABOUT)
		{
			
		}

		// *** file OPs ***
		// new
		if (wParam == IDC_BUTTON_FILE_NEW)
		{
			FileNew();
		}

		// load
		if (wParam == IDC_BUTTON_FILE_LOAD)
		{
			
		}

		// save
		if (wParam == IDC_BUTTON_FILE_SAVE)
		{
			
		}

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


	case WM_PAINT:

		// test
		//DrawPixels(hDlg);

		break;

	}


	return 0;
}


void PKDialog::FileNew(void)
{
	// reset previous grid state
	//

	// define name
	//

	// create new grid
	// FORMAT:
	// by default create grid with rows=1, cols=1
	m_HPGrid.NodeRect_RowAdd();
	m_HPGrid.NodeRect_ColAdd();

}


void PKDialog::FileLoad(void)
{

}


void PKDialog::FileSave(void)
{

}

// ** support **
void PKDialog::UpdateControls_Size(void)
{
	char strBuf[32];

	// row_count
	sprintf(strBuf, "%d", m_HPGrid.NodeRect_GetRowCount);

	HWND m_hRows = GetDlgItem(m_hWndParent, IDC_STATIC_ROW_COUNT);
	SetWindowText(m_hRows, (LPCWSTR)strBuf);

	// col_count

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

