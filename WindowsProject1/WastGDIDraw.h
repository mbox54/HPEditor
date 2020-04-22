// WastGDIDraw.h
// interface file
//
// class WastGDIDraw
// - purpose of class to implement graphics for HPEditor
// * HPEditor uses WinAPI windows
// * WastGDIDraw use GDI as graphics
// date: 09.02.2020

// pragma once
#ifndef WASTGDIDRAW_H

////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////
#include "project.h"
#include "hpcore/hhexlogic.h"
#include "hpcore/hgrid.h"


////////////////////////////////////////////////////////////
// class WastGDIDraw
////////////////////////////////////////////////////////////
class WastGDIDraw
{
	// defines
	static constexpr WORD CANVAS_LAYOUTS_DEFAULT = 10;
	static constexpr WORD CANVAS_WIDTH_DEFAULT = 1200;
	static constexpr WORD CANVAS_HEIGTH_DEFAULT = 1000;
	static constexpr WORD FIGURE_HEX_SIDEA = 80;

	// typedefs
	struct st_PenStyle
	{
		int iStyle;
		int cWidth;
		COLORREF color;
	};

	// consts
	const struct st_PenStyle mc_stGridBackground =
	{
		PS_SOLID,
		4,
		RGB(200, 200, 200)
	};

	const struct st_PenStyle mc_stGridGeneral =
	{
		PS_SOLID,
		2,
		RGB(80, 80, 80)
	};

public:	

	// constructor
	WastGDIDraw();
	WastGDIDraw(HWND hWnd);
	~WastGDIDraw();

	// *** properties ***

	// *** methods ***
	void Init(HWND hWnd);

	void SetGridObject(HGrid* pGrid);

	// Paint current view screen
	void Draw();



private:

	// *** properties ***
	// pointer to the canvas window
	HWND m_hWnd;

	// canvas window parameters
	RECT m_canvasRect;
	RECT m_layouts;
	POINT m_pictureSize;

	// picture params
	WORD m_usFigureHexSideA;
	POINT m_pictureGridSize;

	// coords of centers for grid of hex
	Hhexlogic <POINT> mv_HexPts;

	// hex_grid logic object
	HGrid* m_pGrid;


	// *** methods ***
	void Defaults(void);
	void SetupGridLogic(void);

	//void SetCanvas(CStaticHP* p_CanvasHP);
	//void SetGridGraphInfo();

	// test
	void DrawPixels();

	// figures composite
	// NOTE:
	// HDC resource is system global, it got and returned every Paint time.
	void PaintGridCenterPoints(HDC hdc);
	void PaintGridBackground(HDC hdc);
	void PaintGridRect(HDC hdc);

	// figures primitives	
	void PaintHex(HDC hdc, POINT ptCoord, WORD usSideA, HPEN hPen);
	//// > > Graphics
	//// Canvas sourse
	//CStaticHP* p_CanvasHP;
	
	//// localize Variable usage
	//vectGraphGridInfo* p_GridGraphInfo;	// pointer to /set of Nodes Info/ from Canvas

	// methods
};


#endif // !WASTGDIDRAW_H

