// Schatze.h

// \ INFO
// *******************************************************************
// ['Schatze' = 'Resource']
// Class for define 'Resource' instance
// Have automatization metods for member Unit
// *******************************************************************

// implementation file


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Schatze.h"


// -------------------------------------------------------------------
// class CSchatze
// -------------------------------------------------------------------
CSchatze::CSchatze()
{

}


CSchatze::~CSchatze()
{

}


void CSchatze::AddLinienzugKnot(stLinienzugKnot strucLinienzugKnot)
{

	// allocate memory: Sector in 2x Cell /in Vector container
	this->v_Linienzug.push_back(strucLinienzugKnot);

}

WORD CSchatze::GetLinienzugSize()
{
	WORD usTemp = this->v_Linienzug.size();

	return usTemp;
}


void CSchatze::TestInit()
{
	stLinienzugKnot strucLinienzugKnot;

	// fill test Value
	for (BYTE k = 0; k < 10; k++)
	{

		strucLinienzugKnot.xyCoord.x = k;
		strucLinienzugKnot.xyCoord.y = k;

		strucLinienzugKnot.ucPos = 0;
	}

	// place 
	this->AddLinienzugKnot(strucLinienzugKnot);

}


// INFO:
// algorithm description:
// 1. use as FIRST knot the top left knot
// 2. define position direction relate on next knot
// 3. proceed to the next knot in sequence until the end
void CSchatze::InitLinienzugPositions()
{
	// knots iterator
	// NOTE: MAX knots count = 65535
	WORD usSI = 0;

	// position direction
	// init Value = RIGHT
	BYTE ucP = P_RIGHT;

	// set init knot:
	// SI = 0, P(0) = Right
	this->v_Linienzug[0].ucPos = P_RIGHT;

	// proc knot sequence
	WORD usCount = this->v_Linienzug.capacity();

	POINT xyCoordDiff;

	while (usSI < usCount)
	{
		// go to the next knot
		usSI++;

		// define direction difference
		xyCoordDiff.x = this->v_Linienzug[usSI].xyCoord.x - this->v_Linienzug[usSI - 1].xyCoord.x;
		xyCoordDiff.y = this->v_Linienzug[usSI].xyCoord.y - this->v_Linienzug[usSI - 1].xyCoord.y;

		// define Position direction
		// INFO:
		// knot sequence has adjacent knot with MAX difference = 1
		switch (ucP)
		{
		case P_NOINIT:
			// err case
			break;


		case P_UP:
			if (xyCoordDiff.x == 1)
			{
				// [ X+ ]

				if (xyCoordDiff.y == 1)
				{
					// [ Y+ ]

					this->v_Linienzug[usSI].ucPos = P_LEFT;
					this->v_Linienzug[usSI - 1].ucPos = P_LEFT;
				}
				else if (xyCoordDiff.y == -1)
				{
					// [ Y- ]

					this->v_Linienzug[usSI].ucPos = P_RIGHT;
				}

			}
			else if (xyCoordDiff.x == -1)
			{
				// [ X- ]

				if (xyCoordDiff.y == 1)
				{
					// [ Y+ ]

					this->v_Linienzug[usSI].ucPos = P_RIGHT;
					this->v_Linienzug[usSI - 1].ucPos = P_RIGHT;
				}
				else if (xyCoordDiff.y == -1)
				{
					// [ Y- ]

					this->v_Linienzug[usSI].ucPos = P_LEFT;
				}
			}						

			break;

		case P_DOWN:
			if (xyCoordDiff.x == 1)
			{
				// [ X+ ]

				if (xyCoordDiff.y == 1)
				{
					// [ Y+ ]

					this->v_Linienzug[usSI].ucPos = P_RIGHT;
				}
				else if (xyCoordDiff.y == -1)
				{
					// [ Y- ]

					this->v_Linienzug[usSI].ucPos = P_LEFT;
					this->v_Linienzug[usSI - 1].ucPos = P_LEFT;
				}

			}
			else if (xyCoordDiff.x == -1)
			{
				// [ X- ]

				if (xyCoordDiff.y == 1)
				{
					// [ Y+ ]

					this->v_Linienzug[usSI].ucPos = P_LEFT;
				}
				else if (xyCoordDiff.y == -1)
				{
					// [ Y- ]

					this->v_Linienzug[usSI].ucPos = P_RIGHT;
					this->v_Linienzug[usSI - 1].ucPos = P_RIGHT;

				}
			}

			break;


		case P_LEFT:

			if (xyCoordDiff.x == 0)
			{
				// [ X0 ]
				// [ Y+ ][ Y- ]

				this->v_Linienzug[usSI].ucPos = P_LEFT;

			}
			else if (xyCoordDiff.x == 1)
			{
				// [ X+ ]
				// [ TODO: only Y0 case used now! need to expand]

				this->v_Linienzug[usSI].ucPos = P_DOWN;
			}
			else if (xyCoordDiff.x == -1)
			{
				// [ X- ]
				// [ TODO: only Y0 case used now! need to expand]

				this->v_Linienzug[usSI].ucPos = P_UP;
			}

			break;


		case P_RIGHT:
			if (xyCoordDiff.x == 0)
			{
				// [ X0 ]
				// [ Y+ ][ Y- ]

				this->v_Linienzug[usSI].ucPos = P_RIGHT;

			}
			else if (xyCoordDiff.x == 1)
			{
				// [ X+ ]
				// [ TODO: only Y0 case used now! need to expand]

				this->v_Linienzug[usSI].ucPos = P_UP;
			}
			else if (xyCoordDiff.x == -1)
			{
				// [ X- ]
				// [ TODO: only Y0 case used now! need to expand]

				this->v_Linienzug[usSI].ucPos = P_DOWN;
			}

			break;


		default:
			// err case
			break;
		}//switch (ucP)

	}//while (usSI < usCount)



}


BYTE CSchatze::DefineLinienzugCrossing()
{
	//
	return 0;
}
