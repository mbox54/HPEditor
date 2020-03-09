// Trasse.cpp

// \ INFO
// *******************************************************************
// ['Trasse' = 'Route/Path/Way']
// Class [LOGIC] for define set of Path's 
// Struc Unit
// *******************************************************************

// implementation file

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "../project.h"
#include "trasse.h"

// ===================================================================
// class CTrasse
// ===================================================================
CTrasse::CTrasse()
{

}


// Add new element /weg path/
void CTrasse::Add(CWeg wegPath)
{
	l_Trasse.emplace_back(wegPath);
}


CTrasse::~CTrasse()
{

}
