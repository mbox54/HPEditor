// Sector.h

// \ INFO
// *******************************************************************
// Class for Hex_Plot Sector representation
// define Coord point in Node
// CGridHP <- CPlotHP <- CNodeHP <- HSector
// *******************************************************************


// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////
// support
#include "globals.h"

// load/save xml file
#include "../external/tinyxml2.h"


//////////////////////////////////////////////////////////////////////
// class HSector
//////////////////////////////////////////////////////////////////////
class HSector
{
public:
	// standard constructor
	HSector();
	HSector(POINT pt_GridPos, POINT pt_NodePos);


	// +++++++++++++++++++
	// # Properties
	// +++++++++++++++++++
	// NOTE: need to define directory when Save/Load File OP
	POINT m_NodePosition;

	// # Net Position
	// NOTE: graphic /user when Save/Load File OP
	POINT m_position;

	// Borders: Allowed directions
	BYTE v_incidence[6];

	// # Internal
	BYTE m_altitude;

	// +++++++++++++++++++
	// > Methods
	// +++++++++++++++++++
	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// Init
	void Init();


	// File OPs
	void Save();
	void Load();

	// test
	void DebugBillet01(void);
	//....................................................................


	~HSector();

};

