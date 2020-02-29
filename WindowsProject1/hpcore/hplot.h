// PlotHP.h

// \ INFO
// *******************************************************************
// Class for Hex_Plot Plot representation
// define Plot common logic
// Container Unit
// CGridHP <- HPlot <- CNodeHP <- HSector
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////
// container objects
#include "hnode.h"

// load/save xml file
#include "../external/tinyxml2.h"

// std vector container
#include <vector>



// side size Parameter
#define SIDESIZE 12				// NOTE: HexGrid Size: x12 = dozens


// -------------------------------------------------------------------
// class HPlot
// -------------------------------------------------------------------
class HPlot
{
public:
	// standard constructor
	HPlot();
	HPlot(POINT gridPos);


	// destructor
	~HPlot();

	// > Properties
	// > > Net Position
	POINT m_position;		// graphic /unused

	POINT m_gridSize;

	std::vector < std::vector< HNode > > v_NodesHP;

	// Borders: Allowed directions
	BYTE v_incidence[6];


	// > Methods
	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// Init
	void Init(void);
	void Load(void);

	// SW: alias to abstract specisic vector push function
	void AddNode(POINT gridPos);
	// HW: need to locate in memory vector container elements
	void ExpandGrid(void);

};

