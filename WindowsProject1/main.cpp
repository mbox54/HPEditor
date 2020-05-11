// main.cpp
// HP Editor application file

// *** plans TODO: ***
// 09.02.20
// + [09.02.20] [28.03.20] draw Grid (main level0 grid)
// - [09.02.20] load Grid from file.xml
// + [09.02.20] [16.02.20] find a concept to separate graphic engine from Wast-project core logic
// - [09.02.20] save Grid to file.xml
// + [23.02.20] [01.03.20] place Wast Grid logic here
// - [01.03.20] place CMD "new" with empty wast file in dialog
// + [01.03.20] [22.04.20] prepare function for CMD "new" with empty HPGrid and support
// + [01.03.20] [09.03.20] complete nodes base OPs in "hhexlogic"
// + [09.03.20] [09.03.20] complete nodes extended OPs in "hhexlogic"
// - [22.04.20] link main dialog controls to rect_grid size
// - [22.04.20] perform actions for Buttons addRow, addCol, delRow, delCol
// - [22.04.20] perform OnMouse event to shift active hex_cell hover cursor


////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////
#include "project.h"
#include "pkdialog.h"
#include "hpcore/globals.h"


////////////////////////////////////////////////////////////
// function
////////////////////////////////////////////////////////////
// main
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// init global config for Grid
	Config_Init();

	// new main Dialog instance
	PKDialog mainDlg(hInstance, IDD_DIALOG_MAIN, HWND_DESKTOP);

	// show main dialog
	mainDlg.DoModal();

	
	return 0;
}
