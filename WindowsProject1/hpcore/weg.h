// Weg.h

// \ INFO
// *******************************************************************
// ['Weg' = 'Channel/Track']
// Class for define one Path/Way 
// Struc Unit
// Logic
// *******************************************************************

// NOTE:
// L1 Container
// 1 Weg = N stHPWeg
// CTrasse <- CWeg <- stHPWeg


// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include <list>


//////////////////////////////////////////////////////////////////////
// Typedefs
//////////////////////////////////////////////////////////////////////

// Weg Waypoint Knot
typedef struct stWegKnot
{
	POINT xyCoord;

	WORD uiNumber;
};


// -------------------------------------------------------------------
// class CWeg
// -------------------------------------------------------------------
class CWeg
{
public:
	// standard constructor
	CWeg();

	// > Properties
	// Weg, the set of WegKnots
	std::list<stWegKnot> l_Weg;

	// > Methods
	void Add(stWegKnot wegKnot);

	~CWeg();

};

