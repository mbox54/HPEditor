// WastGDIDraw.h
// interface file
//
// class WastGDIDraw
// - purpose of class to implement graphics for HPEditor
// * HPEditor uses WinAPI windows
// * WastGDIDraw use GDI as graphics
// date: 09.02.2020

#ifndef WASTGDIDRAW_H

////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////
#include "project.h"


////////////////////////////////////////////////////////////
// class WastGDIDraw
////////////////////////////////////////////////////////////
class WastGDIDraw
{
public:
	// constructor
	WastGDIDraw();
	WastGDIDraw(HWND hWnd);

	~WastGDIDraw();

	// properties

	// methods
	void Init(HWND hWnd);

	// test
	void DrawPixels();


private:
	// > properties
	// pointer to the canvas window
	HWND m_hWnd;

	// canvas window parameters
	RECT m_canvasRect;



	// methods
};


#endif // !WASTGDIDRAW_H

