// hhlogic.h

// \ INFO
////////////////////////////////////////////////////////////
// Class for Hex plot properties operations 
// define Hex map common logic
// base class for all hex plot typed classes
// this class has generic type for node type, so
// this class is template class
// it assumed, that specialisation wil be used in derived class
// moreover purpose of this class is to be derived
////////////////////////////////////////////////////////////

// interface file

#pragma once


////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
// typedefs
#include "../project.h"
// Sys: Support
#include <vector>							
// Routing
#include "trasse.h"	


////////////////////////////////////////////////////////////
// class Hhexlogic
////////////////////////////////////////////////////////////
template <class T>
class Hhexlogic
{
static constexpr WORD MAX_SIZE_ROWS_DEFAULT = 48;
static constexpr WORD MAX_SIZE_COLS_DEFAULT = 48;


public:
	// constuctor
	Hhexlogic();
	Hhexlogic(POINT gridSize);

	~Hhexlogic();


	// * * * properties * * *
	// > > Node Container
	// dementions size
	POINT m_gridSize;
	POINT mc_gridMaxSize;

	// Borders: Allowed directions, as core node
	BYTE mv_incidence[6];

	// node container
	std::vector < std::vector< T > > mv_grid;
	
	// service buffer for copy-paste
	std::vector< T > mv_tempBuf;

	// Trasse of Nodes
	CTrasse m_Trasse;

	// * * * methods * * *
	void Init();

	// nodes / base
	void NodeRowAdd();
	void NodeColAdd(WORD usRowIndex);
	void NodeRowRemove();
	void NodeColRemove(WORD usRowIndex);
	void NodeRowPaste(WORD usIndex);
	void NodeColPaste(WORD usRowIndex, WORD usIndex);
	void NodeRowCut(WORD usIndex);
	void NodeColCut(WORD usRowIndex, WORD usIndex);
	// nodes / extended
	void NodeRect_RowAdd();
	void NodeRect_ColAdd();
	void NodeRect_RowRemove();
	void NodeRect_ColRemove();

	// node / file
	void LoadNode(POINT gridPos);

	// with grid
	void SetGridSize(POINT gridSize);
	void UpdateGridMemory();

	// set up in memory
	void PlaceGrid(void);

	// logic: find straight line point-to-point
	void StraightWeg(POINT nodeFirst, POINT nodeLast, CWeg* p_wegOutput);


	// virtual, rewrited
	// File OPs
	void Save();
	void Load();


private:

};



