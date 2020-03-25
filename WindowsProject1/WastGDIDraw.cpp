// WastGDIDraw.c
// implementation file


////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////
// precompile
#include "project.h"
#include "WastGDIDraw.h"


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
	WORD usHexColCount = m_pictureSize.x / m_usFigureHexSideA;
	float fh = m_usFigureHexSideA * sqrt(3) / 2;
	WORD usH = (WORD)fh;
	if (usH - fh > 0.5)
	{
		usH++;
	}

	float fHeigth = m_pictureSize.y / fh;
	WORD usHexRowCount = (WORD)fHeigth;
	if (usHexRowCount - fHeigth > 0.5)
	{
		usHexRowCount++;
	}

	// create logic
	m_pictureGridSize.x = usHexColCount;
	m_pictureGridSize.y = usHexRowCount;

	mv_HexPts.NodeRect_PlaceNewGrid(m_pictureGridSize);

	// fill coords
	float fCoord;
	for (WORD y = 0; y < usHexRowCount; y++)
	{
		for (WORD x = 0; x < usHexColCount; x++)
		{
			mv_HexPts.mv_grid[y][x].x = m_usFigureHexSideA * x + (m_usFigureHexSideA / 2) * (y % 2);

			fCoord = y * fh;
			mv_HexPts.mv_grid[y][x].y = (WORD)fCoord;
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
	GridCenterPoints(hdc);

	// draw hex
	Hex(hdc, mv_HexPts.mv_grid[4][5], m_usFigureHexSideA);
	Hex(hdc, mv_HexPts.mv_grid[4][6], m_usFigureHexSideA);
	Hex(hdc, mv_HexPts.mv_grid[5][5], m_usFigureHexSideA);
	Hex(hdc, mv_HexPts.mv_grid[1][4], m_usFigureHexSideA);
	Hex(hdc, mv_HexPts.mv_grid[8][6], m_usFigureHexSideA);
	Hex(hdc, mv_HexPts.mv_grid[2][9], m_usFigureHexSideA);
	Hex(hdc, mv_HexPts.mv_grid[9][11], m_usFigureHexSideA);

	// # release resources
	EndPaint(m_hWnd, &ps);
}


void WastGDIDraw::GridCenterPoints(HDC hdc)
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

// FORMAT:
// a		.....#..... 
// bl, br	..#.....#..
// cl, cr	..#.....#..
// d		.....#.....
// o - coord center
void WastGDIDraw::Hex(HDC hdc, POINT ptCoord, WORD usSideA)
{
	// accelerate float operations
	float fSqrt3SideA = usSideA * sqrt(3);
	WORD usSqrt3SideA = (WORD)fSqrt3SideA;
	if (fSqrt3SideA - usSqrt3SideA > 0.5)
	{
		usSqrt3SideA++;
	}

	// coords store vector
	POINT v_ptHex[6];

	// NOTE: 
	// not actually optimized, direct calculation approach

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

	// draw figure
	Polygon(hdc, v_ptHex, 6);
}


/*
// TODO:
// transfer to this class

// Prepare Information for Grid -> Graphic Picture Controller
void CGridHP::FormGraphInfo()
{
	// NOTE: use GraphTrasm struc DataType

	// localize Grid size
	POINT grph_Size = this->m_gridSize;

	// construct Graph Grid-Net Info
	POINT CoordGrid;

	for (WORD uiCoorX = 0; uiCoorX < grph_Size.x; uiCoorX++)
	{
		// allocate memory: Vector for Row /in NodeGraphInfo struc container
		this->p_GridGraphInfo->push_back(std::vector<stHPNodeGraphInfo>());

		// Fill Cols
		for (WORD uiCoorY = 0; uiCoorY < grph_Size.y; uiCoorY++)
		{
			// define Coord to set
			CoordGrid.x = uiCoorX;
			CoordGrid.y = uiCoorY;

			// create NodeGraphInfo instance
			stHPNodeGraphInfo HPNodeGraphInfo;

			// Form Node Info-Value for Graph OPs
			BYTE ucNodeValue;
			this->v_Nodes[uiCoorX][uiCoorY].FormGraphInfo(&ucNodeValue);
			HPNodeGraphInfo.Value = ucNodeValue;


			// allocate memory: NodeGraphInfo in 2x Cell /in NodeGraphInfo struc Vector container
			// fill with Value
			this->p_GridGraphInfo->at(uiCoorX).push_back(HPNodeGraphInfo);
		}
	}//for (WORD uiCoorX / WORD uiCoorX)

}

// Paint Grid on Graphic Control
// NOTE: use Canvas vars for PROC Graph parameters, TRASM to Paint
void CGridHP::PaintGrid()
{
	// > Define Grid_Net Set-of-Nodes
	// forming Node Graph Info
	this->FormGraphInfo();

	// > Call subordinate: Paint PROC
	this->p_CanvasHP->PaintGrid();
}

// Set control /Canvas/
void CGridHP::SetCanvas(CStaticHP * p_CanvasHP)
{
	// Set Canvas source
	this->p_CanvasHP = p_CanvasHP;

	// Set Graph Info source from Canvas
	SetGridGraphInfo();
}

// Set struc /Values: size, Nodes/
void CGridHP::SetGridGraphInfo()
{
	// set Pointer /v_GridGraphInfo/ to Variable MemAddr [INPUT]
	this->p_GridGraphInfo = &this->p_CanvasHP->v_GridGraphInfo;

	// set Pointer /GridSize/ to Variable MemAddr [OUTPUT]
	this->p_CanvasHP->p_gridSize = &this->m_gridSize;

}

*/