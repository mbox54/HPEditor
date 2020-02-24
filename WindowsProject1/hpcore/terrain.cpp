// Terrain.h

// \ INFO
// *******************************************************************
// ['Terrain' = 'Ground/nature type']
// Class for define 'Nature type' instance
// Struc Unit
// *******************************************************************

// implementation file

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Terrain.h"


// -------------------------------------------------------------------
// class CTerrain
// -------------------------------------------------------------------
CTerrain::CTerrain()
{
	// init
	Init();

}


CTerrain::~CTerrain()
{

}


void CTerrain::Init()
{
	// init base properties
	this->m_TerrainType = 3;
}
