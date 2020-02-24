// Schatze.h

// \ INFO
// *******************************************************************
// ['Schatze' = 'Resource']
// Class for define 'Resource' instance
// Have automatization metods for member Unit
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include <vector>

//////////////////////////////////////////////////////////////////////
// Defines
//////////////////////////////////////////////////////////////////////
#define P_NOINIT		0
#define P_UP			1
#define P_LEFT			2
#define P_DOWN			3
#define P_RIGHT			4


//////////////////////////////////////////////////////////////////////
// Typedefs
//////////////////////////////////////////////////////////////////////

// Linienzug Knot
// ['Linienzug' = 'Kontur']
//
// NOTE:
// FORMAT:
// # 'Pos' Values: 
// - noinit		0
// - UP			1
// - LEFT		2
// - DOWN		3
// - RIGHT		4
typedef struct stLinienzugKnot
{
	// grid position
	POINT xyCoord;	

	// markers
	BYTE ucPos;
};


// -------------------------------------------------------------------
// class CSchatze
// -------------------------------------------------------------------
class CSchatze
{
public:
	// standard constructor
	CSchatze();

	~CSchatze();

	// > Properties
	BYTE m_ucResouceType;

	std::vector<stLinienzugKnot> v_Linienzug;

	// > Methods
	// common 
	void AddLinienzugKnot(stLinienzugKnot strucLinienzugKnot);	
	WORD GetLinienzugSize();

	void TestInit();

	// starter initialization, define Pos Values 
	void InitLinienzugPositions();

	// define State of 'Point' crossing 'Kontur' on demand
	BYTE DefineLinienzugCrossing();

};

