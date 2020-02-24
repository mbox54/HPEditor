// hhlogic.h

// \ INFO
// ***********************************************************************
// Class for Hex plot properties operations 
// define Hex map common logic
// base class for all hex plot typed classes
// this class has generic type for node type, so
// this class is template class
// it assumed, that specialisation wil be used in derived class
// moreover purpose of this class is to be derived
// ***********************************************************************

// interface file

#pragma once


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////
// typedefs
#include "../project.h"
// Sys: Support
#include <vector>							
// Routing
#include "trasse.h"	


// -------------------------------------------------------------------
// class Hhexlogic
// -------------------------------------------------------------------
template <class T>
class Hhexlogic
{
public:
	// constuctor
	Hhexlogic();
	~Hhexlogic();


	// * * * properties * * *
	// > > Node Container
	// dementions size
	POINT m_gridSize;

	// Borders: Allowed directions, as core node
	BYTE mv_incidence[6];

	// node container
	std::vector < std::vector< T > > mv_grid;
	

	// * * * methods * * *
	// with nodes
	void AddNode(POINT gridPos);
	void LoadNode(POINT gridPos);

	// with grid
	void SetGridSize(POINT gridSize);
	
	// set up in memory
	void PlaceGridNull(void);
	void PlaceGridFill(void);

	// logic: find straight line point-to-point
	void StraightWeg(POINT nodeFirst, POINT nodeLast, CWeg* p_wegOutput);


	// virtual, rewrited
	// File OPs
	void Save();
	void Load();


private:

};



