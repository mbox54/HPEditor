// WastGDIDraw.c
// implementation file


////////////////////////////////////////////////////////////
// includes
////////////////////////////////////////////////////////////
// precompile
#include "project.h"
#include "WastGDIDraw.h"


////////////////////////////////////////////////////////////
// consts
////////////////////////////////////////////////////////////
const struct st_PenStyle mc_stGridBackground =
{
	PS_SOLID,
	4,
	RGB(200, 200, 200)
};



////////////////////////////////////////////////////////////
// class WastGDIDraw
////////////////////////////////////////////////////////////
WastGDIDraw::WastGDIDraw()
{
	// defaults
	m_hWnd = 0;

	m_canvasRect.bottom = 0;
	m_canvasRect.left = 0;
	m_canvasRect.right = 0;
	m_canvasRect.top = 0;

	Defaults();
}


WastGDIDraw::WastGDIDraw(HWND hWnd)
{
	// set up 
	m_hWnd = hWnd;

	GetClientRect(m_hWnd, &m_canvasRect);

	Defaults();
	SetupGridLogic();
}


WastGDIDraw::~WastGDIDraw()
{

}


void WastGDIDraw::Defaults(void)
{
	m_layouts.left = CANVAS_LAYOUTS_DEFAULT;
	m_layouts.right = CANVAS_LAYOUTS_DEFAULT;
	m_layouts.top = CANVAS_LAYOUTS_DEFAULT;
	m_layouts.bottom = CANVAS_LAYOUTS_DEFAULT;

	m_pictureSize.x = CANVAS_WIDTH_DEFAULT;
	m_pictureSize.y = CANVAS_HEIGTH_DEFAULT;

	m_usFigureHexSideA = FIGURE_HEX_SIDEA;

	m_pictureGridSize.x = 0;
	m_pictureGridSize.y = 0;
}


void WastGDIDraw::SetupGridLogic(void)
{
	// init grid logic
	// define coord centers

	// NOTE:
	// because Col position relate on "+(m_usFigureHexSideA / 2) * (y % 2)"
	// need to decrement ColCount 
	WORD usHexColCount = m_pictureSize.x / m_usFigureHexSideA - 1;
	float fh = m_usFigureHexSideA * sqrt(3) / 2;
	WORD usH = (WORD)fh;

	WORD usHexRowCount = m_pictureSize.y / usH;

	// create logic
	m_pictureGridSize.x = usHexColCount;
	m_pictureGridSize.y = usHexRowCount;

	mv_HexPts.NodeRect_PlaceNewGrid(m_pictureGridSize);

	// fill coords
	for (WORD y = 0; y < usHexRowCount; y++)
	{
		// NOTE:
		// 'x' and 'y' coord need to be shifted by 0.5 hex-size because (x, y) is centers of figure
		for (WORD x = 0; x < usHexColCount; x++)
		{
			mv_HexPts.mv_grid[y][x].x = m_usFigureHexSideA * x + (m_usFigureHexSideA / 2) * (y % 2) + m_usFigureHexSideA / 2;
			mv_HexPts.mv_grid[y][x].y = y * usH + usH * 2 / 3;
		}
	}
}


void WastGDIDraw::Init(HWND hWnd)
{
	// set up window values
	m_hWnd = hWnd;

	GetClientRect(m_hWnd, &m_canvasRect);

	SetupGridLogic();
}


void WastGDIDraw::DrawPixels()
{
	PAINTSTRUCT ps;

	if (m_canvasRect.bottom == 0) {

		return;
	}

	HDC hdc = BeginPaint(m_hWnd, &ps);

	for (int i = 0; i < 1000; i++) {

		int x = rand() % m_canvasRect.right;
		int y = rand() % m_canvasRect.bottom;
		SetPixel(hdc, x, y, RGB(255, 0, 0));
	}

	EndPaint(m_hWnd, &ps);
}



void WastGDIDraw::Draw()
{
	// # init paint parameters
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hWnd, &ps);

	// set proportional equal demention sizes x = y
	SetMapMode(hdc, MM_ISOTROPIC); 

	// set canvas size in abstract work units
	SetWindowExtEx(hdc, m_pictureSize.x, m_pictureSize.y, NULL);

	// set max canvas draw coords position
	SetViewportExtEx(hdc, 
		m_canvasRect.right - m_layouts.right - m_layouts.left, // Right_Max = Right_Display - Right_layout - (Zero_Left + Left_layout)
		-(m_canvasRect.bottom - m_layouts.top - m_layouts.bottom), // also with top
		NULL); 

	// set start canvas draw coord position
	SetViewportOrgEx(hdc, m_layouts.left, m_canvasRect.bottom - m_layouts.bottom, NULL);

	// # paint on canvas
	// test
	//MoveToEx(hdc, 0, 0, NULL);
	//LineTo(hdc, 1200, 1000);
	//LineTo(hdc, 1200, 0);
	//LineTo(hdc, 0, 1000);
	//LineTo(hdc, 0, 500);

	// place Grid blueprint map
	// NOTE:
	// Hex based on equilateral triangle. 
	// - equilateral triangle: side = a, higth = h = a * 3^0.5 / 2
	PaintGridCenterPoints(hdc);

	// paint background grid
	PaintGridBackground(hdc);

	// # release resources
	EndPaint(m_hWnd, &ps);
}


void WastGDIDraw::PaintGridCenterPoints(HDC hdc)
{
	// draw points
	for (WORD y = 0; y < m_pictureGridSize.y; y++)
	{
		for (WORD x = 0; x < m_pictureGridSize.x; x++)
		{
			// draw
			SetPixel(hdc, mv_HexPts.mv_grid[y][x].x, mv_HexPts.mv_grid[y][x].y, RGB(0, 0, 255));
		}
	}
}

// background grid blueprint
void WastGDIDraw::PaintGridBackground(HDC hdc)
{
	// define specific style
	HPEN hPenDraw = CreatePen(mc_stGridBackground.iStyle, mc_stGridBackground.cWidth, mc_stGridBackground.color);

	// draw hexes
	for (WORD y = 0; y < m_pictureGridSize.y; y++)
	{
		for (WORD x = 0; x < m_pictureGridSize.x; x++)
		{
			// draw
			PaintHex(hdc, mv_HexPts.mv_grid[y][x], m_usFigureHexSideA, hPenDraw);
		}
	}
	
}

// FORMAT:
// a		.....#..... 
// bl, br	..#.....#..
// cl, cr	..#.....#..
// d		.....#.....
// o - coord center
void WastGDIDraw::PaintHex(HDC hdc, POINT ptCoord, WORD usSideA, HPEN hPen)
{
	// accelerate float operations
	float fSqrt3SideA = usSideA * sqrt(3);
	WORD usSqrt3SideA = (WORD)fSqrt3SideA;
	if (fSqrt3SideA - usSqrt3SideA > 0.5)
	{
		usSqrt3SideA++;
	}

	// # define points
	// NOTE: 
	// not actually optimized, direct calculation approach

	// coords store vector
	POINT v_ptHex[6];

	// init point = a
	// xa = xo
	// ya = yo + sideA * 3^0.5 / 3
	v_ptHex[0].x = ptCoord.x;
	v_ptHex[0].y = ptCoord.y + usSqrt3SideA / 3;

	// next point = br
	// xbr = xo + sideA / 2
	// ybr = yo + sideA * 3^0.5 / 6
	v_ptHex[1].x = ptCoord.x + usSideA / 2;
	v_ptHex[1].y = ptCoord.y + usSqrt3SideA / 6;

	// next point = cr
	// xcr = xo + sideA / 2
	// ycr = yo - sideA * 3^0.5 / 6
	v_ptHex[2].x = ptCoord.x + usSideA / 2;
	v_ptHex[2].y = ptCoord.y - usSqrt3SideA / 6;

	// next point = d
	// xa = xo
	// ya = yo - sideA * 3^0.5 / 3
	v_ptHex[3].x = ptCoord.x;
	v_ptHex[3].y = ptCoord.y - usSqrt3SideA / 3;

	// next point = cl
	// xcr = xo - sideA / 2
	// ycr = yo - sideA * 3^0.5 / 6
	v_ptHex[4].x = ptCoord.x - usSideA / 2;
	v_ptHex[4].y = ptCoord.y - usSqrt3SideA / 6;

	// next point = bl
	// xbr = xo - sideA / 2
	// ybr = yo + sideA * 3^0.5 / 6
	v_ptHex[5].x = ptCoord.x - usSideA / 2;
	v_ptHex[5].y = ptCoord.y + usSqrt3SideA / 6;

	// # draw figure
	// apply style
	SelectObject(hdc, hPen);

	// draw
	Polygon(hdc, v_ptHex, 6);
}
