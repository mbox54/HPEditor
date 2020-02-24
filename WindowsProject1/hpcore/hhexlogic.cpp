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
template<class T>
Hhexlogic<T>::Hhexlogic()
{
	// defaults
	m_gridSize.x = 0;
	m_gridSize.y = 0;

	for (BYTE k = 0; k < 6; k++)
	{
		// no incident
		mv_incidence[k] = 0;
	}	
}

template<class T>
Hhexlogic<T>::~Hhexlogic()
{

}

template<class T>
void Hhexlogic<T>::AddNode(POINT gridPos)
{
	// check boundaries
	if (gridPos.y < m_gridSize.y)
	{
		// allocate memory: can just push to back element in specific row
		this->mv_grid[gridPos.y].push_back(T);
	}	
}

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

template<class T>
void Hhexlogic<T>::PlaceGridNull(void)
{
	// > Fill Rows
	POINT CoordGrid;

	for (WORD uiCoorY = 0; uiCoorY < this->m_gridSize.y; uiCoorY++)
	{
		// allocate memory: Vector for Row /in Node Vector container
		this->mv_grid.push_back(std::vector< T >());

		// Fill Cols
		for (WORD uiCoorX = 0; uiCoorX < this->m_gridSize.x; uiCoorX++)
		{
			// define Coord to set
			CoordGrid.y = uiCoorY;
			CoordGrid.x = uiCoorX;

			// create Node instance
			CNodeHP NodeHP(CoordGrid);

			// allocate memory: Node in 2x Cell /in Node Vector container
			this->mv_grid[uiCoorY].push_back( T );
		}//for (WORD uiCoorX
	}//for (WORD uiCoorY

}

template<class T>
void Hhexlogic<T>::PlaceGridFill(void)
{
	// > Fill Rows
	POINT CoordGrid;

	for (WORD uiCoorY = 0; uiCoorY < this->m_gridSize.y; uiCoorY++)
	{
		// allocate memory: Vector for Row /in Node Vector container
		this->mv_grid.push_back(std::vector< T >());

		// Fill Cols
		for (WORD uiCoorX = 0; uiCoorX < this->m_gridSize.x; uiCoorX++)
		{
			// define Coord to set
			CoordGrid.y = uiCoorY;
			CoordGrid.x = uiCoorX;

			// create Node instance
			CNodeHP NodeHP(CoordGrid);

			// allocate memory: Node in 2x Cell /in Node Vector container
			this->mv_grid[uiCoorY].push_back(T);

			// Load Node Values
			this->LoadNode(CoordGrid);
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

// virtual
template<class T>
void Hhexlogic<T>::Save()
{
}

template<class T>
void Hhexlogic<T>::Load()
{
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