// NodeHP.h

// \ INFO
// *******************************************************************
// Class for Hex_Plot Node representation
// define Node common logic
// Container Unit
// CGridHP <- HPlot <- HNode <- HSector
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

// support
#include "globals.h"

#include "terrain.h"
#include "schatze.h"

// container objects
#include "hsector.h"

// load/save xml file
#include "../external/tinyxml2.h"

// std vector container
#include <vector>



//////////////////////////////////////////////////////////////////////
// Defines
//////////////////////////////////////////////////////////////////////
// side size Parameter
#define SIDESIZE 12				// NOTE: HexGrid Size: x12 = dozens


// -------------------------------------------------------------------
// class HNode
// -------------------------------------------------------------------
class HNode
{

public:
	// standard constructor
	HNode();
	HNode(POINT pt_NetPos);

	// +++++++++++++++++++
	// # Properties
	// +++++++++++++++++++
	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// # Net Position
	// NOTE: graphic /user when Save/Load File OP
	POINT m_position;		

	// Borders: Allowed directions
	BYTE v_incidence[6];

	// # Sector Container
	POINT m_NetSize;
	
	std::vector < std::vector< HSector > > v_Sectors;

	// # Internal
	// Terrain
	CTerrain m_terrain;

	// Anlage
	

	// +++++++++++++++++++
	// # Methods
	// +++++++++++++++++++
	//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// Init
	void Init();
	void SetInit(POINT gridPos);


	// Sector
	void PlaceNet();
	void FillSectors();
	void HexToMem(POINT pt_Input, POINT * pt_Output);
	void MemToHex(POINT pt_Input, POINT * pt_Output);

	// Get Graph output Data
	void FormGraphInfo(BYTE * ucValue);


	// File OPs
	void Save();
	void Load();

	// test
	void DebugBillet01(void);
	//....................................................................

	~HNode();

};

