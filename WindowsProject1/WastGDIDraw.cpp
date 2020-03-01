// WastGDIDraw.c
// implementation file


////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////
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
}


WastGDIDraw::WastGDIDraw(HWND hWnd)
{
	// set up 
	m_hWnd = hWnd;

	GetClientRect(m_hWnd, &m_canvasRect);
}


WastGDIDraw::~WastGDIDraw()
{

}


void WastGDIDraw::Init(HWND hWnd)
{
	// set up window values
	m_hWnd = hWnd;

	GetClientRect(m_hWnd, &m_canvasRect);
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