// StaticHP.h

// \ INFO
// *******************************************************************
// Class for HexPlot Graphic procedure
// include structures and methods for picturing
// based on CStatic
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "afxwin.h"
#include "HPTypeDefs.h"
#include "PaintDCHP.h"
#include <vector>


//////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////

#define OP_SUCCESS				0x00
#define OP_FAILURE				0x01


// -------------------------------------------------------------------
// class CStaticHP
// -------------------------------------------------------------------
class CStaticHP : public CStatic
{
public:
	// standard constructor
	CStaticHP();

	~CStaticHP();

	// > Properties
	//BYTE uiSize;
	BYTE uiPaintMode;

	// FROM Logic 
	POINT * p_gridSize;		// p_ptGridSize
	POINT * p_plotSize;
	POINT * p_nodeSize;

	// Grid Params
	CRect m_CanvasRect;

	// Graph params
	stHPCanvasParams HPCanvasParams;
	vectGraphGridInfo v_GridGraphInfo;		// set of Nodes Info


	BYTE v_TestBase[10][10] = 
	{
		{ 0,0,0,0,0,0,0,0,0,0 },	// 0
		{ 0,0,0,0,0,0,0,0,0,0 },	// 1
		{ 0,0,0,0,0,0,0,0,0,0 },	// 2
		{ 0,0,0,0,0,0,0,0,0,0 },	// 3
		{ 0,0,0,0,0,0,0,0,0,0 },	// 4
		{ 0,0,0,0,0,0,0,0,0,0 },	// 5
		{ 0,0,0,0,0,0,0,0,0,0 },	// 6
		{ 0,0,0,0,0,0,0,0,0,0 },	// 7
		{ 0,0,0,0,0,0,0,0,0,0 },	// 8
		{ 0,0,0,0,0,0,0,0,0,0 },	// 9
	};

	// > Methods
	void InitTest();
	void SetCanvasRect();
	void PaintGrid();
	void PaintGrid2();

	POINT GetCursorCoords();

	// > Events
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

