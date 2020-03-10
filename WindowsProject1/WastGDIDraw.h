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
	static constexpr WORD CANVAS_LAYOUTS_DEFAULT = 10;


public:	

	// constructor
	WastGDIDraw();
	WastGDIDraw(HWND hWnd);
	//HGrid(CStaticHP* p_CanvasHP);

	~WastGDIDraw();

	// properties

	// methods
	void Init(HWND hWnd);

	//void SetCanvas(CStaticHP* p_CanvasHP);
	//void SetGridGraphInfo();

	// test
	void DrawPixels();

	// Paint current view screen
	void Draw();


private:
	// > properties
	// pointer to the canvas window
	HWND m_hWnd;

	// canvas window parameters
	RECT m_canvasRect;
	RECT m_layouts;

	//// > > Graphics
	//// Canvas sourse
	//CStaticHP* p_CanvasHP;
	
	//// localize Variable usage
	//vectGraphGridInfo* p_GridGraphInfo;	// pointer to /set of Nodes Info/ from Canvas

	// methods
};


#endif // !WASTGDIDRAW_H

