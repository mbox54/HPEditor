// pkdialog.h: interface for the PKDialog class.
//
////////////////////////////////////////////////////////////

#pragma once


////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////
#include "project.h"
#include "WastGDIDraw.h"


////////////////////////////////////////////////////////////
// support classes
////////////////////////////////////////////////////////////
// Common control prototype
class PKControl
{
public:
	// constructor
	PKControl();
	~PKControl();

protected:
	// > properties
	// store control properties relate to control
	int m_nResId = 0;
	HWND m_hWndParent = NULL;
	HWND m_hWnd = NULL;

	// wndproc handle to parent for subclassing implementation
	WNDPROC* m_hPreviousProcHandle = 0;

	// > methods
	// control message loop routine
	LRESULT virtual Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// this handle, need for place CALLBACK proc as dialog method
	// virtual, need to regefine in derived classes
	static long m_lThis;
};



// Edit-'COMMAND'
class Edit_cmd: public PKControl 
{
public:
	// constructor
	Edit_cmd();

	~Edit_cmd();

	// service
	void Init(int nResId, HWND hWndParent, WNDPROC* hMainDlgProcHandle);


	// > properties


	// > methods
	//
	// message loop routine callback static prototype
	static LRESULT CALLBACK ProcStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// control message loop routine
	LRESULT Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// this handle, need for place CALLBACK proc as dialog method
	static long m_lThis;
};


// Picture-'Canvas'
class Canvas: public PKControl
{
public:
	// constructor
	Canvas();

	~Canvas();

	// service
	void Init(int nResId, HWND hWndParent, WNDPROC* hProcHandle);


	// > properties

	// > methods
	//
	// message loop routine callback static prototype
	static LRESULT CALLBACK ProcStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// control message loop routine
	LRESULT Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);	

	// this handle, need for place CALLBACK proc as dialog method
	static long m_lThis;

private:

	// properties
	WastGDIDraw m_Draw;

	// methods
	void InitCanvas();
	
	void OnPaint();

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

	// show dialog, start message proc
	void DoModal(void);

	// > controls
	Edit_cmd m_Edit_cmd;
	Canvas m_Canvas;


private:
	// *** properties ***
	// service
	HINSTANCE	m_hInstance;
	WORD		m_nResId;
	HWND		m_hWndParent;

	// Need to be global
	// Edit control subclass wnd proc: needs self KeyDown event
	WNDPROC		m_hEditCmd_ProcHandle;

	// Canvas control subclass wnd proc: need paint self event
	WNDPROC		m_hCanvas_ProcHandle;

	// ?
	WNDPROC		m_hProcHandle;

	// this handle, need for place CALLBACK proc as dialog method
	static long m_lThis;
	static HWND m_hWindow;

	// *** methods ***
	// init incorporated contols
	void Init(HWND hDlg);

	// message loop routine callback static prototype
	static BOOL CALLBACK DlgProcStatic(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

	// dialog message loop routine
	BOOL DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

	// file OPs
	void FileNew(void);
	void FileLoad(void);
	void FileSave(void);
	
	
};