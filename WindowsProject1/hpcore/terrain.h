// Terrain.h

// \ INFO
// *******************************************************************
// ['Terrain' = 'Ground/nature type']
// Class for define 'Nature type' instance
// Struc Unit
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////


// -------------------------------------------------------------------
// class CTerrain
// -------------------------------------------------------------------
class CTerrain
{
public:
	// standard constructor
	CTerrain();

	~CTerrain();

	// > Properties
	BYTE m_TerrainType;
	
	// > Methods
	// Init
	void Init();


};

