// GridHP.cpp

// \ INFO
////////////////////////////////////////////////////////////
// Class for Hex_Plot Grid representation
// define Grid common logic
// Grid include Nodes
////////////////////////////////////////////////////////////

// implementation file

#define _CRT_SECURE_NO_WARNINGS


////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include "../project.h"
#include "hgrid.h"


////////////////////////////////////////////////////////////
// class HGrid
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Constructor, init section
//
//HGrid::HGrid()
//{
//	// Init
//	Init();
//
//	// XML FILE OP
//	//!debug
//	/////////////////////////////////////////////////////
//	// NO FILE INITIATION CASE
//	/////////////////////////////////////////////////////
//	// DEBUG: use test config Billet
//	DebugBillet01();
//
//	Load();
//
//	// > Place Net: create Nodes
//	PlaceNet();
//


// Construct & Fill v_Nodes
void HGrid::Init(void)
{
	// ## Default Values
	// NOTE: need when load op failed
	// Init properties	

}


////////////////////////////////////////////////////////////
// Common methods section
//
//void HGrid::AddNode()
//{
//	HNode Node1;
//}
//

//
//
//void HGrid::AddWeg()
//{
//
//}

// Stor WegKnot sequence of Straight WegPath
// NOTE:
// *******************************************
// [#] HexPlot Line Types : 
// 0 = [0  +1], 
// C = [+1  0], 
// 2 = [+1 -1], 
// 3 = [0  -1], 
// 4 = [-1  0], 
// 5 = [-1 +1].
//
//
// [#] exist N direction cases:
// direct:	case |1|, |3| = X-coord; case |0|, |3| = Y-coord
// combine: case |2|, |5| = Z-coord
// 
//
// [#] /dX/ | /dY/  defines:
// dX > 0 & dY < 0, dX < 0 & dY > 0 = Z-coord
// other = X-, Y-coord.
//
// [#] algorithm with Dijkstra method
// *******************************************
//void HGrid::StraightWeg(POINT nodeFirst, POINT nodeLast, CWeg * p_wegOutput)
//{
//	// define vars, init
//	POINT aPos = nodeFirst;		// start
//	POINT zPos = nodeLast;		// finish
//
//	int dX;						// delta
//	int dY;						// delta
//
//	stWegKnot wegKnot;			// temp struc for WegKnot fill OP
//	WORD k = 0;					// cycle increment
//
//	// > Add init First Node
//	// fill Knot struc
//	wegKnot.uiNumber = k;
//	wegKnot.xyCoord = aPos;
//
//	// add to OutputVar
//	p_wegOutput->Add(wegKnot);
//
//	k++;
//
//	// repeat sequentially for each StraightWeg WegKnot needed
//	// Step by step
//	BYTE act = 1;
//	while (act)
//	{
//		// > Define dX | dY
//		dX = zPos.x - aPos.x;	// delta
//		dY = zPos.y - aPos.y;	// delta
//
//		// > Check end cycle
//		if ((dX == 0) && (dY == 0))
//		{
//			// [FINAL NODE HAS BEING ARRIVED]
//
//			act = 0;
//		}
//		else
//		{
//			// [WAY PROCEED]
//
//			// > Check OZ inclusion: combine case
//			if ( ( (dX < 0) && (dY > 0) ) || ( (dX > 0) && (dY < 0) ) )
//			{
//				// [INCLUDE OZ]
//
//				// check direction
//				if (dX > 0)
//				{
//					// [POS]: HPDir = 2
//
//					// move to new Pos
//					aPos.x++;
//					aPos.y--;
//				}
//				else
//				{
//					// [NEG]: HPDir = 5
//
//					// move to new Pos
//					aPos.x--;
//					aPos.y++;
//				}
//			}//then: [INCLUDE OZ]/ Check OZ inclusion: combine case
//			else
//			{
//				// [NOT INCLUDE OZ]
//				// simple case
//
//				// > Check OX POS Dir
//				if (dX > 0)
//				{
//					// [POS]: HPDir = 1
//
//					// move to new Pos
//					aPos.x++;
//				}
//				else
//				{
//					// > Check OX NEG Dir
//					if (dX < 0)
//					{					
//						// [NEG]: HPDir = 4
//
//						// move to new Pos
//						aPos.x--;
//					}
//					else
//					{
//						// [NOT INCLUDE OX]
//
//						// > Check OY POS Dir
//						if (dY > 0)
//						{
//							// [POS]: HPDir = 0
//
//							// move to new Pos
//							aPos.y++;
//						}
//						else
//						{
//							// > Check OY NEG Dir
//							if (dY < 0)
//							{
//								// [NEG]: HPDir = 3
//
//								// move to new Pos
//								aPos.y--;
//							}
//							else
//							{
//								// [NOT INCLUDE OY]
//
//								// strange condition:
//								// no OZ, no OX, no OY. MUST dX = dY = 0.
//
//								act = 0;
//							}// > Check OY NEG Dir
//						}// > Check OY POS Dir
//					}// > Check OX NEG Dir
//				}// > Check OX POS Dir
//			}//else/ > Check OZ inclusion: combine case
//
//			// > Add WegKnot
//			// fill Knot struc
//			wegKnot.uiNumber = k;
//			wegKnot.xyCoord = aPos;
//
//			// add to OutputVar
//			p_wegOutput->Add(wegKnot);
//
//			k++;
//
//		}// > Check end cycle, if ((dX == 0) && (dY == 0))
//
//	}//while (act)
//}
//
//// Stor WegKnot sequence of best WegPath
//// Estimate minimal cost to complete path [nodeFirst -> nodeLast]
//void HGrid::EstimateWegCost(POINT nodeFirst, POINT nodeLast)
//{
//
//
//}

////////////////////////////////////////////////////////////
// FILE XML OPs

void HGrid::Save()
{
	// # Form Document
	tinyxml2::XMLDocument WDocument;

	// # Form XML Header
	char * str_XMLSpec = (char*)"xml version=\"1.0\" encoding=\"windows - 1251\" standalone=\"yes\"";
	tinyxml2::XMLDeclaration* WDeclaration = WDocument.NewDeclaration((char const*)str_XMLSpec);
	WDocument.LinkEndChild(WDeclaration);

	tinyxml2::XMLComment* CmntDeclaration = WDocument.NewComment("WAST Grid file structure");
	WDocument.LinkEndChild(CmntDeclaration);

	// # Form Wast root element
	tinyxml2::XMLElement* El_Root = WDocument.NewElement("WAST");
	WDocument.LinkEndChild(El_Root);

	tinyxml2::XMLElement* WastPart = WDocument.NewElement("Part");
	WastPart->SetText("GRID");
	El_Root->InsertEndChild(WastPart);

	// # Form Title Part
	tinyxml2::XMLComment* CmntTitle = WDocument.NewComment("Part: Title");
	El_Root->InsertEndChild(CmntTitle);

	tinyxml2::XMLElement* El_Title = WDocument.NewElement("TITLE");
	El_Root->InsertEndChild(El_Title);

	// > Title Content
	// Description
	tinyxml2::XMLElement* El_Tit_Desc = WDocument.NewElement("Descr");
	El_Tit_Desc->SetText("Wast File, contained Grid structure filled with data");
	El_Title->InsertEndChild(El_Tit_Desc);

	// Date
	tinyxml2::XMLElement* El_Tit_Date = WDocument.NewElement("Date");
	El_Tit_Date->SetText("Save PROC Date: 141117 10.00");
	El_Title->InsertEndChild(El_Tit_Date);

	// Node grid size
	tinyxml2::XMLElement* El_Tit_Nodes = WDocument.NewElement("Nodes");
	El_Title->InsertEndChild(El_Tit_Nodes);

	tinyxml2::XMLElement* El_Tit_Nodes_X = WDocument.NewElement("X");
	El_Tit_Nodes_X->SetText(m_gridSize.x);
	El_Tit_Nodes->InsertEndChild(El_Tit_Nodes_X);

	tinyxml2::XMLElement* El_Tit_Nodes_Y = WDocument.NewElement("Y");
	El_Tit_Nodes_Y->SetText(m_gridSize.y);
	El_Tit_Nodes->InsertEndChild(El_Tit_Nodes_Y);


	// # Form Body
	tinyxml2::XMLComment* CmntBody = WDocument.NewComment("Part: Body");
	El_Root->InsertEndChild(CmntBody);

	tinyxml2::XMLElement* El_Body = WDocument.NewElement("BODY");
	El_Root->InsertEndChild(El_Body);

	// # Body Content
	// Node
	for (BYTE ky = 0; ky < m_gridSize.y; ky++)
	{
		for (BYTE kx = 0; kx < m_gridSize.x; kx++)
		{
			tinyxml2::XMLElement* El_Node = WDocument.NewElement("Node");
			El_Node->SetAttribute("Y", ky);
			El_Node->SetAttribute("X", kx);
			El_Node->SetText(kx * ky);
			El_Body->InsertEndChild(El_Node);
		}		
	}

	// # Save Document
	char strFileName[128];
	strcpy(strFileName, m_stGlobals.cDirectoryPath);
	strcat(strFileName, "\\");
	strcat(strFileName, m_stGlobals.strWastName);

	// Create Node directory
	CreateDirectory((LPCWSTR)strFileName, NULL);
	
	strcat(strFileName, "\\Grid.xml");

	WDocument.SaveFile(strFileName);
}
//
//
//void HGrid::Load()
//{
//	// > Form Document
//	tinyxml2::XMLDocument WDocument;
//
//	// > Load Document
//	char strFileName[128];
//	strcpy(strFileName, m_stGlobals.cDirectoryPath);
//	strcat(strFileName, "\\");
//	strcat(strFileName, m_strWastName);
//	strcat(strFileName, "\\Grid.xml");
//
//	WDocument.LoadFile(strFileName);
//
//	// > Parse Title Part
//	tinyxml2::XMLElement* El_Root = WDocument.FirstChildElement("WAST");
//	tinyxml2::XMLElement* El_Title = El_Root->FirstChildElement("TITLE");
//
//	// > Title Content
//	// grid size: Plots
//	// NOTE:
//	// need to perform Node -> Plot
//	tinyxml2::XMLElement* El_Tit_Nodes = El_Title->FirstChildElement("Nodes");
//
//	// - property: size
//	tinyxml2::XMLElement* El_Tit_Nodes_X = El_Tit_Nodes->FirstChildElement("X");
//	int iVal = 0;
//	El_Tit_Nodes_X->QueryIntText(&iVal);
//	m_gridSize.x = iVal;
//
//	tinyxml2::XMLElement* El_Tit_Nodes_Y = El_Tit_Nodes->FirstChildElement("Y");
//	El_Tit_Nodes_Y->QueryIntText(&iVal);
//	m_gridSize.y = iVal;
//
//}


//////////////////////////////////////////////////////////////////////
// Debug, Test section
//
void HGrid::DebugBillet01(void)
{
	// > Set Grid size work instance
	// Set Grid Size
	//POINT Point_temp;
	//Point_temp.x = 1;
	//Point_temp.y = 1;

	//this->m_gridSize = Point_temp;

	//// 

	//// > Save
	//// set instance Name
	//strcpy(m_strWastName, "System1");

	//Save();
}

// Test functionality
void HGrid::Test()
{
	// test FILE OPs
	//Save();

	//this->v_Nodes[1][2].Save();

	// test StraightWeg PROC
	//POINT coorFirs;
	//POINT coorLast;

	//coorFirs.x = 5;
	//coorFirs.y = 5;

	//coorLast.x = 10;
	//coorLast.y = 10;

	//CWeg weg_tmp;

	//this->StraightWeg(coorFirs, coorLast, &weg_tmp);
}