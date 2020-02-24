// Trasse.h

// \ INFO
// *******************************************************************
// ['Trasse' = 'Route/Path/Way']
// Class for define set of Path's 
// Struc Unit
// Logic
// *******************************************************************

// NOTE:
// L2 Container
// 1 Trasse = N Weg's
// CTrasse <- CWeg <- stHPWeg


// interface file

#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "Weg.h"
#include <list>


// -------------------------------------------------------------------
// class CTrasse
// -------------------------------------------------------------------
class CTrasse
{
public:
	// standard constructor
	CTrasse();

	// > Properties
	// Trasse
	std::list<CWeg> l_Trasse;


	// > Methods
	void Add(CWeg wegPath);


	~CTrasse();
};

