// Trasse.cpp

// \ INFO
// *******************************************************************
// ['Weg' = 'Path/Direction']
// Class for define one Path/Way 
// Struc Unit
// Logic
// *******************************************************************

// implementation file

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Weg.h"


// -------------------------------------------------------------------
// class CWeg
// -------------------------------------------------------------------
CWeg::CWeg()
{

}


// Add new element /weg point/
void CWeg::Add(stWegKnot wegKnot)
{
	l_Weg.emplace_back(wegKnot);
}


CWeg::~CWeg()
{

}
