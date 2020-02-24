// PaintNode.h

// \ INFO
// *******************************************************************
// Class for PaintDC HexPlot Graphics
// include additional procedures for HexPlot Node graphics
// based on CPaintDC
// *******************************************************************

// implementation file


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PaintNode.h"


// ===================================================================
// class CPaintNode
// ===================================================================

CPaintNode::CPaintNode(CWnd* pWnd) : CPaintDC(pWnd) // using parent constructor
{

}


CPaintNode::CPaintNode(CWnd * pWnd, POINT * p_gridSize, stHPCanvasParams * pHPGridImage)
	: CPaintDC(pWnd) // using parent constructor
{
	this->p_ptNodeSize = p_gridSize;
	this->pHPCanvasParams = pHPGridImage;
}


void CPaintNode::SetGridImageStruc(stHPCanvasParams * pHPGridImage)
{
	this->pHPCanvasParams = pHPGridImage;
}


void CPaintNode::Circle(int x, int y)
{
	// Localize Vars	
	WORD uiThick = this->pHPCanvasParams->HPNodeParams.ucWeigth;

	uiThick /= 2;

	// Paint
	this->Ellipse(x - uiThick, y + uiThick, x + uiThick, y - uiThick);

}

// clause
void CPaintNode::Circle(POINT Coord)
{
	Circle(Coord.x, Coord.y);
}


void CPaintNode::Sector(int x, int y)
{
	// Save Pen prev
	CPen * Pen_Prev(GetCurrentPen());

	// Set Pen style
	CPen Pen_Act(PS_SOLID, 4, RGB(50, 100, 200));

	this->SelectObject(Pen_Act);

	// Localize Vars
	POINT ProcCoor;
	BYTE ucLineLength = this->pHPCanvasParams->HPNodeParams.ucLength;

	// Define Canvas Coord
	ProcCoor.x = this->pHPCanvasParams->HPNodeParams.uiOXPadding + x * ucLineLength + y * ucLineLength / 2;
	ProcCoor.y = this->pHPCanvasParams->HPNodeParams.uiOYPadding - y * ucLineLength * 1.732 / 2;

	// > Paint
	this->Circle(ProcCoor);

	// Restore Pen prev
	this->SelectObject(Pen_Prev);

}

// clause
void CPaintNode::Sector(POINT Coord)
{
	this->Sector(Coord.x, Coord.y);
}


// NOTE: 
// FORMAT: 
// HexPlot Line Types : 
// 0 = [0  +1], 
// 1 = [+1  0], 
// 2 = [+1 -1], 
// 3 = [0  -1], 
// 4 = [-1  0], 
// 5 = [-1 +1].
void CPaintNode::Line(int x, int y, BYTE LineType)
{
	// Localize Vars
	POINT ProcCoor;
	BYTE ucLineLength = this->pHPCanvasParams->HPGridParams.ucLength;

	// Define Canvas Coord
	ProcCoor.x = this->pHPCanvasParams->HPGridParams.uiOXPadding + x * ucLineLength + y * ucLineLength / 2;
	ProcCoor.y = this->pHPCanvasParams->HPGridParams.uiOYPadding - y * ucLineLength * 1.732 / 2;

	// Move Pen Pointer to Node Center
	MoveTo(ProcCoor);

	// Line to define direction
	switch (LineType)
	{
	case 0:
		ProcCoor.x += ucLineLength / 4;
		ProcCoor.y -= ucLineLength * 1.732 / 4;

		break;

	case 1:
		ProcCoor.x += ucLineLength / 2;
		// ProcCoor.y NONE

		break;

	case 2:
		ProcCoor.x -= ucLineLength / 4;
		ProcCoor.y += ucLineLength * 1.732 / 4;

		break;

	case 3:
		ProcCoor.x += ucLineLength / 4;
		ProcCoor.y += ucLineLength * 1.732 / 4;

		break;

	case 4:
		ProcCoor.x -= ucLineLength / 2;
		// ProcCoor.y NONE

		break;

	case 5:
		ProcCoor.x -= ucLineLength / 4;
		ProcCoor.y -= ucLineLength * 1.732 / 4;

		break;

	default:

		// err case
		break;
	}

	LineTo(ProcCoor);

}

// clause
void CPaintNode::Line(POINT Coord, BYTE LineType)
{
	Line(Coord.x, Coord.y, LineType);

}

// Paint Node content
void CPaintNode::Node()
{
	// each Sector of Node
	for (WORD k_x = 0; k_x < this->p_ptNodeSize->x; k_x++)
	{
		for (BYTE k_y = 0; k_y < this->p_ptNodeSize->y; k_y++)
		{
			// Lines
			for (BYTE k_line = 0; k_line < 6; k_line++)
			{
				// if 
				this->Line(k_x, k_y, k_line);
			}

			// Sector
			this->Sector(k_x, k_y);
		}
	}

}


CPaintNode::~CPaintNode()
{

}
