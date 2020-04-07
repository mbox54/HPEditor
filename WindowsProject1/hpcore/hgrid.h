// GridHP.h

// \ INFO
////////////////////////////////////////////////////////////
// Class for Hex_Plot Grid representation
// define Grid common logic
// Grid include Nodes
// HGrid <- HPlot <- CNodeHP <- HSector
////////////////////////////////////////////////////////////

// interface file

#pragma once


////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////

// parent grid structure
#include "hhexlogic.h"

// nodes
#include "hplot.h"		

// service /typedef /system ops
#include "globals.h"

// load/save xml file
#include "../external/tinyxml2.h"

// std vector container
#include <vector>


////////////////////////////////////////////////////////////
// class HGrid
////////////////////////////////////////////////////////////
class HGrid : public Hhexlogic<HPlot>
{
	#define SIDESIZE 20


public:
	// standard constructor
	HGrid() : Hhexlogic<HPlot>() 
	{
		// specific inits
		Init();
	};

	// > Properties
	// > > Node Container
//	POINT m_gridSize;
//	std::vector < std::vector< HPlot > > mv_grid;

	// *** methods ***
	// Logic
	// Node OP

	// File OPs
	void Save();
	void Load();

	// Test
	void DebugBillet01(void);
	void Test();


private:

	// *** methods ***

	void Init(void);
};

