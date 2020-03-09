// hhlogic.cpp

// \ INFO
// ***********************************************************************
// Class for Hex plot properties operations 
// define Hex map common logic
// base class for all hex plot typed classes
// ***********************************************************************

// implementation file

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////
// precompile
#include "../project.h"
// interface
#include "hhexlogic.h"


// -------------------------------------------------------------------
// class Hhexlogic
// -------------------------------------------------------------------
// NOTE:
// New/Load usecases:
// 1. from NULL
// - create NULL object by calling Hhexlogic(), 
// - set grid size by calling SetGridSize(POINT gridSize)
// + load nodes by calling LoadNode(POINT gridPos)
// + load all nodes by calling Load()
// + work with empty nodes, fill it by self
//
// 2. load immediately
// - create with size param, Hhexlogic(POINT gridSize)
// + load nodes by calling LoadNode(POINT gridPos)
// + load all nodes by calling Load()
// + work with empty nodes, fill it by self
//


template<class T>
Hhexlogic<T>::Hhexlogic()
{
	// defaults
	Init();
}

template<class T>
Hhexlogic<T>::Hhexlogic(POINT gridSize)
{
	m_gridSize = gridSize;
}

template<class T>
Hhexlogic<T>::~Hhexlogic()
{

}

template<class T>
void Hhexlogic<T>::Init()
{
	// defaults
	m_gridSize.x = 0;
	m_gridSize.y = 0;

	mc_gridMaxSize.y = MAX_SIZE_ROWS_DEFAULT;
	mc_gridMaxSize.x = MAX_SIZE_COLS_DEFAULT;

	for (BYTE k = 0; k < 6; k++)
	{
		// no incident
		mv_incidence[k] = 0;
	}
}

// Node operations
// NOTE:
// structure of usage:
// NodeRowAdd()						pushes node to end
// NodeColAdd()						pushes node to end
// NodeRowRemove()					remove last node
// NodeColRemove()					remove last node
// NodeRowPaste(usIndex)			inserts node upon Index
// NodeColPaste(usIndex)			inserts node upon Index
// NodeRowCut(usIndex)				deletes node upon Index
// NodeColCut(usIndex)				deletes node upon Index
// UpdateGridMemory()				edit mv_grid upon m_gridSize
// SetGridSize(gridSize)			sets m_gridSize upon gridSize, call UpdateGridMemory()
//
//
//
// FORMAT:
//		X00	X01	X02	X03	...	Xi	...	XN
// YM	[#]	[#]	[#]	[#]	[#]	[#]	[#]	[#]
// ...	[#]	[#]	[#]	[#]	[#]	[#]	[#]	[#]
// Yj	[#]	[#]	[#]	[#]	[#]	[#]	[#]	[#]
// ...	[#]	[#]	[#]	[#]	[#]	[#]	[#]	[#]
// Y03	[#]	[#]	[#]	[#]	[#]	[#]	[#]	[#]
// Y02	[#]	[#]	[#]	[#]	[#]	[#]	[#]	[#]
// Y01	[#]	[#]	[#]	[#]	[#]	[#]	[#]	[#]
//
// Y = Row, X = Col
//
// vector structure mv_grid has specific:
// Allocate Row ---> Allocate Col, Allocate Col, Allocate Col,
// Allocate Row ---> Allocate Col, Allocate Col, Allocate Col,
// Allocate Row ---> Allocate Col, Allocate Col, Allocate Col,
// ...
// mv_grid[Y][X] has (Y, X) placement order
// vector mv_grid[gridPos.y][gridPos.x]

template<class T>
void Hhexlogic<T>::NodeRowAdd()
{
	// check max boundaries
	if (m_gridSize.y < mc_gridMaxSize.y)
	{
		// [VALID]

		// add row
		// allocate memory: just push to back
		this->mv_grid.push_back(T);

		// inc Row count
		m_gridSize.y++;
	}
	else
	{
		// [INVALID: EXCEED_MAX]

		return;
	}
}

// NOTE: in this (vector) approach to implement [x,y] grid
// there are some constraints exist:
// 'X' elements may be various on any 'Y', not equal in every 'Y'
// so if equal value must be performed, 
// that work must be controlled by developer. I.e. in spec function.
template<class T>
void Hhexlogic<T>::NodeColAdd(WORD usRowIndex)
{
	// check max boundaries
	WORD usColCount = mv_grid.capacity();

	if (usColCount < mc_gridMaxSize.x)
	{
		// [VALID]

		// add col
		// allocate memory: just push to back element in specific row
		this->mv_grid[usRowIndex].push_back(T);

		// inc Col count
		// NOTE: not applied here now
		//usColCount++;
	}
	else
	{
		// [INVALID: EXCEED_MAX]

		return;
	}
}

template<class T>
void Hhexlogic<T>::NodeRowRemove()
{
	// check min boundaries
	if (m_gridSize.y > 0)
	{
		// [VALID]

		// delete row
		// allocate memory: just pop back element
		this->mv_grid.pop_back();

		// inc Row count
		m_gridSize.y--;
	}
	else
	{
		// [INVALID: EXCEED_MAX]

		return;
	}
}

// NOTE: in this (vector) approach to implement [x,y] grid
// there are some constraints exist:
// 'X' elements may be various on any 'Y', not equal in every 'Y'
// so if equal value must be performed, 
// that work must be controlled by developer. I.e. in spec function.
template<class T>
void Hhexlogic<T>::NodeColRemove(WORD usRowIndex)
{
	// check min boundaries
	WORD usColCount = mv_grid.capacity();

	if (usColCount > 0)
	{
		// [VALID]

		// delete col
		// allocate memory: just pop back element in specific row
		this->mv_grid[usRowIndex].pop_back();

		// dec Col count
		// NOTE: not applied here now
		//usColCount--;
	}
	else
	{
		// [INVALID: EXCEED_MAX]

		return;
	}
}

template<class T>
void Hhexlogic<T>::NodeRowPaste(WORD usIndex)
{
	// check max boundaries
	if (m_gridSize.y < mc_gridMaxSize.y)
	{
		// [VALID]

		// add row
		// allocate memory: insert element in specific position
		this->mv_grid.insert(usIndex, T);

		// inc Row count
		m_gridSize.y++;
	}
	else
	{
		// [INVALID: EXCEED_MAX]

		return;
	}
}

template<class T>
void Hhexlogic<T>::NodeColPaste(WORD usRowIndex, WORD usIndex)
{
	// check max boundaries
	WORD usColCount = mv_grid.capacity();

	if (usColCount < mc_gridMaxSize.x)
	{
		// [VALID]

		// add col
		// allocate memory: insert element in specific position in specific row
		this->mv_grid[usRowIndex].insert(usIndex, T);

		// inc Col count
		// NOTE: not applied here now
		//usColCount++;
	}
	else
	{
		// [INVALID: EXCEED_MAX]

		return;
	}
}

template<class T>
void Hhexlogic<T>::NodeRowCut(WORD usIndex)
{
	// check min boundaries
	if (m_gridSize.y > 0)
	{
		// [VALID]

		// cut row
		// delete from position, move elements to empty pos
		this->mv_grid.erase(usIndex);

		// inc Row count
		m_gridSize.y--;
	}
	else
	{
		// [INVALID: EXCEED_MAX]

		return;
	}
}

template<class T>
void Hhexlogic<T>::NodeColCut(WORD usRowIndex, WORD usIndex)
{
	// check min boundaries
	WORD usColCount = mv_grid.capacity();

	if (usColCount > 0)
	{
		// [VALID]

		// cut col
		// allocate memory: just pop back element in specific row
		this->mv_grid[usRowIndex].erase(usIndex);

		// dec Col count
		// NOTE: not applied here now
		//usColCount--;
	}
	else
	{
		// [INVALID: EXCEED_MAX]

		return;
	}
}

template<class T>
void Hhexlogic<T>::UpdateGridMemory()
{

}


// file ops
template<class T>
void Hhexlogic<T>::LoadNode(POINT gridPos)
{
	// NOTE:
	// Load() method must exist in T class!
	this->mv_grid[gridPos.y][gridPos.x].Load();
}

// methods
template<class T>
void Hhexlogic<T>::SetGridSize(POINT gridSize)
{
	this->m_gridSize = gridSize;
}

// Place Defined Node-Unit Net in Memory
// NOTE:
// FORMAT:
// Y = RowNumber, X = ColNumber
//
// vector structure v_Nodes has specific:
// Allocate Row ---> Allocate Col, Allocate Col, Allocate Col,
// Allocate Row ---> Allocate Col, Allocate Col, Allocate Col,
// Allocate Row ---> Allocate Col, Allocate Col, Allocate Col,
// ...
// so v_Nodes[Y][X] has (Y, X) placement order
template<class T>
void Hhexlogic<T>::PlaceGrid(void)
{
	// > Fill Rows
	for (WORD uiCoorY = 0; uiCoorY < this->m_gridSize.y; uiCoorY++)
	{
		// allocate memory: Vector for Row /in Node Vector container
		this->mv_grid.push_back(std::vector< T >());

		// Fill Cols
		for (WORD uiCoorX = 0; uiCoorX < this->m_gridSize.x; uiCoorX++)
		{
			// allocate memory: Node in 2x Cell /in Node Vector container
			this->mv_grid[uiCoorY].push_back( T );
		}//for (WORD uiCoorX

	}//for (WORD uiCoorY

}

// straight shortest line from nodeFirst to nodeLast
template<class T>
void Hhexlogic<T>::StraightWeg(POINT nodeFirst, POINT nodeLast, CWeg* p_wegOutput)
{
	// define vars, init
	POINT aPos = nodeFirst;		// start
	POINT zPos = nodeLast;		// finish

	int dX;						// delta
	int dY;						// delta

	stWegKnot wegKnot;			// temp struc for WegKnot fill OP
	WORD k = 0;					// cycle increment

	// > Add init First Node
	// fill Knot struc
	wegKnot.uiNumber = k;
	wegKnot.xyCoord = aPos;

	// add to OutputVar
	p_wegOutput->Add(wegKnot);

	k++;

	// repeat sequentially for each StraightWeg WegKnot needed
	// Step by step
	BYTE act = 1;
	while (act)
	{
		// > Define dX | dY
		dX = zPos.x - aPos.x;	// delta
		dY = zPos.y - aPos.y;	// delta

		// > Check end cycle
		if ((dX == 0) && (dY == 0))
		{
			// [FINAL NODE HAS BEING ARRIVED]

			act = 0;
		}
		else
		{
			// [WAY PROCEED]

			// > Check OZ inclusion: combine case
			if (((dX < 0) && (dY > 0)) || ((dX > 0) && (dY < 0)))
			{
				// [INCLUDE OZ]

				// check direction
				if (dX > 0)
				{
					// [POS]: HPDir = 2

					// move to new Pos
					aPos.x++;
					aPos.y--;
				}
				else
				{
					// [NEG]: HPDir = 5

					// move to new Pos
					aPos.x--;
					aPos.y++;
				}
			}//then: [INCLUDE OZ]/ Check OZ inclusion: combine case
			else
			{
				// [NOT INCLUDE OZ]
				// simple case

				// > Check OX POS Dir
				if (dX > 0)
				{
					// [POS]: HPDir = 1

					// move to new Pos
					aPos.x++;
				}
				else
				{
					// > Check OX NEG Dir
					if (dX < 0)
					{
						// [NEG]: HPDir = 4

						// move to new Pos
						aPos.x--;
					}
					else
					{
						// [NOT INCLUDE OX]

						// > Check OY POS Dir
						if (dY > 0)
						{
							// [POS]: HPDir = 0

							// move to new Pos
							aPos.y++;
						}
						else
						{
							// > Check OY NEG Dir
							if (dY < 0)
							{
								// [NEG]: HPDir = 3

								// move to new Pos
								aPos.y--;
							}
							else
							{
								// [NOT INCLUDE OY]

								// strange condition:
								// no OZ, no OX, no OY. MUST dX = dY = 0.

								act = 0;
							}// > Check OY NEG Dir
						}// > Check OY POS Dir
					}// > Check OX NEG Dir
				}// > Check OX POS Dir
			}//else/ > Check OZ inclusion: combine case

			// > Add WegKnot
			// fill Knot struc
			wegKnot.uiNumber = k;
			wegKnot.xyCoord = aPos;

			// add to OutputVar
			p_wegOutput->Add(wegKnot);

			k++;

		}// > Check end cycle, if ((dX == 0) && (dY == 0))

	}//while (act)
}


template<class T>
void Hhexlogic<T>::Save()
{
}

// Load Grid: Size, v_Nodes From File/Base
template<class T>
void Hhexlogic<T>::Load()
{
	//for (WORD uiCoorY = 0; uiCoorY < this->m_gridSize.y; uiCoorY++)
	//{
	//	for (WORD uiCoorX = 0; uiCoorX < this->m_gridSize.x; uiCoorX++)
	//	{
	//		// fill node with stored data
	//		this->mv_grid[gridPos.y][gridPos.x].Load();
	//	}
	//}
}

// archive
//void HNode::FillSectors()
//{
//	// FORMAT:
//	// Hex Grid positioning
//	// y: 0 - i - N/2, x: 0 - i - N/2 = NULL, x: N/2 - i - N = VALL
//	// y: N/2 - i - N, x: 0 - i - N/2 = VALL, x: N/2 - i - N = NULL
//	// STRUC: v_Sectors[Y][X]
//
//	// > Set Grid Size
//	POINT pt_Size;
//	pt_Size.x = SIDESIZE;
//	pt_Size.y = SIDESIZE;
//
//	this->m_NetSize = pt_Size;
//
//	// > Fill
//	// Define HexCoords
//	POINT pt_CoordHex;
//		
//
//	BYTE ucXFirst = pt_Size.x / 2;
//	BYTE ucXLength = pt_Size.x / 2;
//
//	BYTE act = 1;
//	char sign = 1;
//
//	// > Proceed Coords
//	pt_CoordHex.y = 0;
//	while (act != 0)
//	{		
//		// Proc mode
//		// Note: 2 modes: 1 = 0--N/2; 2 = N/2--N. 
//		if (act == 1)
//		{
//			// [MODE 1]
//
//			// check mode change
//			if (pt_CoordHex.y > pt_Size.y / 2 - 1)
//			{
//				// [CHANGE]
//
//				sign = -1;
//
//				act = 2;
//			}
//		}//then /if (act == 1)
//		else
//		{
//			if (act == 2)
//			{
//				// [MODE 2]
//
//				// check mode change
//				if (pt_CoordHex.y > pt_Size.y - 1)
//				{
//					// [EXIT]
//
//					act = 0;
//				}
//			}//if (act == 2)			
//		}//else /if (act == 1)
//
//		// Allocate memory: Vector for Row /in Sector Vector container
//		this->v_Sectors.push_back(std::vector<CSector>());
//
//		// Proceed Row: iterate Cols
//		BYTE ucXLast = ucXFirst + ucXLength;
//
//		pt_CoordHex.x = ucXFirst;
//		while (pt_CoordHex.x < ucXLast)
//		{
//			// > Proc Coord
//			// Create Sector instance / init with Hex Coord
//			CSector Sector(m_position, pt_CoordHex);
//
//			// allocate memory: Sector in 2x Cell /in Vector container
//			this->v_Sectors[pt_CoordHex.y].push_back(Sector);
//
//			pt_CoordHex.x++;
//		}
//
//		// Correct Col
//		ucXFirst -= sign;
//		ucXLength += sign;
//
//		pt_CoordHex.y++;
//
//	}//while (act != 0)
//
//}