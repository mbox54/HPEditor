// HexAlgorithm.cpp

// \ INFO
// *******************************************************************
// Library source with service Functions
// Functions for Hex Grid Operation:
// - Functions for calculate / perform Hex Plot way - find algorithm
// *******************************************************************

// implementation file

#include "stdafx.h"
#include "HexAlgorithm.h"


void FillGrid(BYTE * v_HexGrid, BYTE ucSize)
{
	for (int i = 0; i < ucSize; i++)
	{
		for (int j = 0; j < ucSize; j++)
		{
			*(v_HexGrid + i * ucSize + j) = 5;
		}
	}

}