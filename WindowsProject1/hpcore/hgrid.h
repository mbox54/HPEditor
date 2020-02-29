// GridHP.h

// \ INFO
// ***********************************************************************
// Class for Hex_Plot Grid representation
// define Grid common logic
// Grid include Nodes
// HGrid <- HPlot <- CNodeHP <- HSector
// ***********************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////
#include "hplot.h"		
// Routing
#include "trasse.h"						

// load/save xml file
#include "../external/tinyxml2.h"

//#include "external\tinyxml2.h"			// File OPs
#include <vector>							// Sys: Support


//////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////
// side size Parameter
#define SIDESIZE 20


//////////////////////////////////////////////////////////////////////
// Externs
//////////////////////////////////////////////////////////////////////
extern char strWastName[32];


// =======================================================================
// class HGrid
// =======================================================================
// template <typename T>
// class HGrid : public Hhexlogic<HPlot>
class HGrid 
{
public:
	// standard constructor
	HGrid();

	// > Properties
	// > > Node Container
	POINT m_gridSize;
	std::vector < std::vector< HPlot > > mv_grid;

	// Trasse of Nodes
//	CTrasse m_Trasse;


	// > Methods
	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// Init
	void Init();
	void PlaceNet();

	// InProc
	void SetGridSize(POINT gridSize);

	// > > Logic
	// Node OP
	//void AddNode();
	void LoadNode(POINT gridPos);

	void AddWeg();
	void StraightWeg(POINT nodeFirst, POINT nodeLast, CWeg * p_wegOutput);
	void EstimateWegCost(POINT nodeFirst, POINT nodeLast);

	// > > Graphic
	// Native
	//void FormGraphInfo();
	//void PaintGrid();

	// File OPs
	void Save();
	void Load();

	// Test
	void DebugBillet01(void);
	void Test();
	//........................................................................

	~HGrid();
};

