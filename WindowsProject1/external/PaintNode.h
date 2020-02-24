// PaintNode.h

// \ INFO
// *******************************************************************
// Class for PaintDC HexPlot Graphics
// include additional procedures for HexPlot Node graphics
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
// class CPaintNode
// ===================================================================
class CPaintNode : public CPaintDC
{
public:
	// standard constructor
	CPaintNode(CWnd* pWnd);

	CPaintNode(CWnd* pWnd, POINT * p_gridSize, stHPCanvasParams * pHPCanvasParams);

	~CPaintNode();


	// > Properties
	// size
	POINT * p_ptNodeSize;

	// Graph Params
	stHPCanvasParams * pHPCanvasParams;

	// > Events
	void SetGridImageStruc(stHPCanvasParams * pHPGridImage);

	// Figures
	void Circle(int x, int y);
	void Circle(POINT Coord);		// clause

	// Node
	void Sector(int x, int y);
	void Sector(POINT Coord);		// clause

	// Line
	// NOTE: FORMAT: Line to XY / 0 = O, 1 = P(os), -1 = N(eg)
	// NOTE: HexPlot relations: [+1 0], [-1 0], [0 +1], [0 -1], [+1 -1], [-1 +1].  
	void Line(int x, int y, BYTE LineType);
	void Line(POINT Coord, BYTE LineType);

	void LinePO(int x, int y);

	// Grid
	void Node();


};

