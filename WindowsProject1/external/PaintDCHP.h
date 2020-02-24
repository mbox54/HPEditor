// PaintDCHP.h

// \ INFO
// *******************************************************************
// Class for PaintDC HexPlot Graphics
// include additional procedures for HexPlot Grid graphics
// based on CPaintDC
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "afxwin.h"
#include "HPTypeDefs.h"


//////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////

//

// ===================================================================
// class CPaintDCHP
// ===================================================================
class CPaintDCHP : public CPaintDC
{
public:
	// standard constructor
	CPaintDCHP(CWnd* pWnd);

	CPaintDCHP(CWnd* pWnd, POINT * p_gridSize, stHPCanvasParams * pHPGridImage);

	~CPaintDCHP();


	// > Properties
	// size
	POINT * p_gridSize;

	// Graph Params
	stHPCanvasParams * pHPCanvasParams;


	// > Events
	void SetGridImageStruc(stHPCanvasParams * pHPGridImage);

	// Figures
	void Circle(int x, int y);
	void Circle(POINT Coord);		// clause
	
	// Node
	void Node(int x, int y);
	void Node(POINT Coord);			// clause

	// Line
	// NOTE: FORMAT: Line to XY / 0 = O, 1 = P(os), -1 = N(eg)
	// NOTE: HexPlot relations: [+1 0], [-1 0], [0 +1], [0 -1], [+1 -1], [-1 +1].  
	void Line(int x, int y, BYTE LineType);
	void Line(POINT Coord, BYTE LineType);

	void LinePO(int x, int y);

	// Grid
	void Grid();

};

