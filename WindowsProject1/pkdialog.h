// pkdialog.h: interface for the PKDialog class.
//
//////////////////////////////////////////////////////////////////////

#pragma once


////////////////////////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////////////////////////
#include "project.h"


////////////////////////////////////////////////////////////////////////////////
// dialog class
////////////////////////////////////////////////////////////////////////////////
class PKDialog
{
public:
	// constructor
	PKDialog(HINSTANCE hInstance, int nResId, HWND hWndParent);
	~PKDialog();

	// service
	void Init(void);

	// show dialog, start message proc
	void DoModal(void);


private:
	// service
	HINSTANCE	m_hInstance;
	WORD		m_nResId;
	HWND		m_hWndParent;

	// Edit control needs self KeyDown event
	WNDPROC		m_hMainProcHandle;
	WNDPROC		m_hProcHandle;

	// message loop routine callback static prototype
	static BOOL CALLBACK DlgProcStatic(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK EditProcStatic(HWND hEdit, UINT msg, WPARAM wParam, LPARAM lParam);

	// dialog message loop routine
	BOOL DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT EditProc(HWND hEdit, UINT msg, WPARAM wParam, LPARAM lParam);


protected:
	// this handle, need for place CALLBACK proc as dialog method
	static long m_lSaveThis;

	static HWND m_hWindow;
	static HWND m_hEdit;

};