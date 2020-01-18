// pkdialog.h: interface for the PKDialog class.
//
////////////////////////////////////////////////////////////

#pragma once


////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////
#include "project.h"


////////////////////////////////////////////////////////////
// support classes
////////////////////////////////////////////////////////////
// Edit-'COMMAND'
class Edit_cmd
{
public:
	// constructor
	Edit_cmd();

	~Edit_cmd();

	// service
	void Init(int nResId, HWND hWndParent, WNDPROC* hMainDlgProcHandle);


	// > properties
	// store dialog properties relate to control
	int m_nResId = 0;
	HWND m_hWndParent = NULL;

	// > methods


private:

	// wndproc handle to parent for subclassing implementation
	WNDPROC* m_hMainDlgProcHandle = 0; 

	//
	// message loop routine callback static prototype
	static LRESULT CALLBACK EditProcStatic(HWND hEdit, UINT msg, WPARAM wParam, LPARAM lParam);

	// control message loop routine
	LRESULT EditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// this handle, need for place CALLBACK proc as dialog method
	static long m_lThis;
};


////////////////////////////////////////////////////////////
// dialog class
////////////////////////////////////////////////////////////
class PKDialog
{
public:
	// constructor
	PKDialog(HINSTANCE hInstance, int nResId, HWND hWndParent);
	~PKDialog();

	// service
	void Init(HWND hDlg);

	// show dialog, start message proc
	void DoModal(void);

	// > controls
	Edit_cmd m_Edit_cmd;

private:
	// service
	HINSTANCE	m_hInstance;
	WORD		m_nResId;
	HWND		m_hWndParent;

	// Edit control needs self KeyDown event
	WNDPROC		m_hMainDlgProcHandle;
	WNDPROC		m_hProcHandle;


	// message loop routine callback static prototype
	static BOOL CALLBACK DlgProcStatic(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
//	static LRESULT CALLBACK EditProcStatic(HWND hEdit, UINT msg, WPARAM wParam, LPARAM lParam);

	// dialog message loop routine
	BOOL DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
//	LRESULT EditProc(HWND hEdit, UINT msg, WPARAM wParam, LPARAM lParam);


protected:
	// this handle, need for place CALLBACK proc as dialog method
	static long m_lThis;

	static HWND m_hWindow;
	
	
};