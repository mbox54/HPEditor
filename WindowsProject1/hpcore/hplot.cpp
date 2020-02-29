// PlotHP.cpp

// \ INFO
// *******************************************************************
// Class for Hex_Plot Plot representation
// define Plot common logic
// Container Unit
// CGridHP <- HPlot <- CNodeHP <- CSector
// *******************************************************************


// implementation file


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////
#include "../project.h"
#include "hplot.h"


// ===================================================================
// class HPlot
// ===================================================================
HPlot::HPlot()
{
	Init();
}


HPlot::HPlot(POINT gridPos)
{
	Init();

	this->m_position = gridPos;
}


HPlot::~HPlot()
{

}


void HPlot::Init(void)
{
	// > Default Values

	// init properties
	// default
	POINT initCoord;
	initCoord.x = 0;
	initCoord.y = 0;

	m_position = initCoord;

	// [addition]

	// incidence /none/
	for (BYTE k = 0; k < 6; k++)
	{
		this->v_incidence[k] = 0;
	}

	// > Load Values
	// ExpandGrid();

}


void HPlot::Load(void)
{
	// > Form Document
	tinyxml2::XMLDocument WDocument;

	// > Load Document
	WDocument.LoadFile("C:\\wast\\WastPlot.xml");

	// > Parse Title Part
	tinyxml2::XMLElement* El_Root = WDocument.FirstChildElement("WAST");
	tinyxml2::XMLElement* El_Title = El_Root->FirstChildElement("TITLE");

	// > Title Content
	// Nodes
	tinyxml2::XMLElement* El_Tit_Nodes = El_Title->FirstChildElement("Nodes");

	// - property: size
	tinyxml2::XMLElement* El_Tit_Nodes_X = El_Tit_Nodes->FirstChildElement("X");
	int iVal = 0;
	El_Tit_Nodes_X->QueryIntText(&iVal);
	m_gridSize.x = iVal;

	tinyxml2::XMLElement* El_Tit_Nodes_Y = El_Tit_Nodes->FirstChildElement("Y");
	El_Tit_Nodes_Y->QueryIntText(&iVal);
	m_gridSize.y = iVal;
}


void HPlot::AddNode(POINT gridPos)
{
	// > check appropriate Count of line
	while (this->v_NodesHP.size() < gridPos.y)
	{
		// [NEED TO ADD LINE]

		// allocate memory: Vector for Row /in Node Vector container
		this->v_NodesHP.push_back(std::vector<HNode>());
	}

	// create Node instance
	HNode Node_inst(gridPos);

	// allocate memory: Node in 2x Cell /in Node Vector container
	this->v_NodesHP[gridPos.y].push_back(Node_inst);
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
void HPlot::ExpandGrid(void)
{
	// > Fill Rows
	POINT CoordGrid;

	for (WORD uiCoorY = 0; uiCoorY < this->m_gridSize.y; uiCoorY++)
	{
		// Fill Cols
		for (WORD uiCoorX = 0; uiCoorX < this->m_gridSize.x; uiCoorX++)
		{
			// define Coord to set
			CoordGrid.y = uiCoorY;
			CoordGrid.x = uiCoorX;

			AddNode(CoordGrid);

			// Load Node Values
			//this->LoadNode(CoordGrid);
		}//for (WORD uiCoorX
	}//for (WORD uiCoorY

}