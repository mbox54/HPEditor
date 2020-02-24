// Sector.cpp

// \ INFO
// *******************************************************************
// Class for Hex_Plot Sector representation
// define Coord point in Node
// CGridHP <- CPlotHP <- CNodeHP <- CSector
// *******************************************************************

// implementation file


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sector.h"


// ===================================================================
// class CSector
// ===================================================================
//////////////////////////////////////////////////////////////////////
// Constructor, init section
//
CSector::CSector()
{
	Init();

}

CSector::CSector(POINT pt_GridPos, POINT pt_NodePos)
{
	// init defaults
	Init();

	// load Values
	m_NodePosition = pt_GridPos;
	m_position = pt_NodePos;

	// > Load Values
	// XML FILE OP
	//!debug
	/////////////////////////////////////////////////////
	// NO FILE INITIATION CASE
	/////////////////////////////////////////////////////
	// DEBUG: use test config Billet
	DebugBillet01();

	Load();
}


CSector::~CSector()
{
}


void CSector::Init()
{
	// ## Default Values
	// NOTE: need when load op failed
	// Init properties

	// Init properties

	// [m_position]
	POINT initCoord;
	initCoord.x = 0;
	initCoord.y = 0;

	m_position = initCoord;

	// [altitude]
	m_altitude = 0;

}

//////////////////////////////////////////////////////////////////////
// FILE XML OPs
//
void CSector::Save()
{
	// # Form Document
	tinyxml2::XMLDocument WDocument;

	// # Form XML Header
	char* str_XMLSpec = "xml version=\"1.0\" encoding=\"windows - 1251\" standalone=\"yes\"";
	tinyxml2::XMLDeclaration* WDeclaration = WDocument.NewDeclaration(str_XMLSpec);
	WDocument.LinkEndChild(WDeclaration);

	tinyxml2::XMLComment* CmntDeclaration = WDocument.NewComment("WAST Sector file structure");
	WDocument.LinkEndChild(CmntDeclaration);

	// # Form Wast root element
	tinyxml2::XMLElement* El_Root = WDocument.NewElement("WAST");
	WDocument.LinkEndChild(El_Root);

	tinyxml2::XMLElement* WastPart = WDocument.NewElement("Part");
	WastPart->SetText("SECTOR");
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


	// # Form Body
	tinyxml2::XMLComment* CmntBody = WDocument.NewComment("Part: Body");
	El_Root->InsertEndChild(CmntBody);

	tinyxml2::XMLElement* El_Body = WDocument.NewElement("BODY");
	El_Root->InsertEndChild(El_Body);

	// # Body Content
	// - property: altitude 
	tinyxml2::XMLElement* Pr_Altitude = WDocument.NewElement("Altitude");
	Pr_Altitude->SetText(m_altitude);
	El_Body->InsertEndChild(Pr_Altitude);

	// # Save Document
	// Form specific Filename (GridName\\NodeY05X08\\SectorY03X04)
	char strFileName[128];
	strcpy(strFileName, m_stGlobals.cDirectoryPath);
	strcat(strFileName, "\\");
	strcat(strFileName, m_strWastName);
	strcat(strFileName, "\\Node");

	strcat(strFileName, "Y");
	char str_buf[8];
	_itoa(m_NodePosition.y, str_buf, 10);
	strcat(strFileName, str_buf);

	strcat(strFileName, "X");
	_itoa(m_NodePosition.x, str_buf, 10);
	strcat(strFileName, str_buf);

	// Create Node directory /is don't exist
	CreateDirectory((CString)strFileName, NULL);

	strcat(strFileName, "\\Sector");

	strcat(strFileName, "Y");
	_itoa(m_position.y, str_buf, 10);
	strcat(strFileName, str_buf);

	strcat(strFileName, "X");
	_itoa(m_position.x, str_buf, 10);
	strcat(strFileName, str_buf);

	// Create Sector directory
	CreateDirectory((CString)strFileName, NULL);

	strcat(strFileName, "\\Sector.xml");

	WDocument.SaveFile(strFileName);
}


void CSector::Load()
{
	// > Form Document
	tinyxml2::XMLDocument WDocument;

	// > Load Document
	// Form specific Filename (GridName\\NodeY05X08\\SectorY03X04)
	char strFileName[128];
	strcpy(strFileName, m_stGlobals.cDirectoryPath);
	strcat(strFileName, "\\");
	strcat(strFileName, m_strWastName);
	strcat(strFileName, "\\Node");

	strcat(strFileName, "Y");
	char str_buf[8];
	_itoa(m_NodePosition.y, str_buf, 10);
	strcat(strFileName, str_buf);

	strcat(strFileName, "X");
	_itoa(m_NodePosition.x, str_buf, 10);
	strcat(strFileName, str_buf);

	strcat(strFileName, "\\Sector");

	strcat(strFileName, "Y");
	_itoa(m_position.y, str_buf, 10);
	strcat(strFileName, str_buf);

	strcat(strFileName, "X");
	_itoa(m_position.x, str_buf, 10);
	strcat(strFileName, str_buf);

	strcat(strFileName, "\\Sector.xml");

	WDocument.LoadFile(strFileName);

	// > Parse Title Part
	tinyxml2::XMLElement* El_Root = WDocument.FirstChildElement("WAST");
	tinyxml2::XMLElement* El_Title = El_Root->FirstChildElement("TITLE");

	// > Title Content
	// Sector info
	// none 

	// > Body Content
	tinyxml2::XMLElement* El_Body = El_Root->FirstChildElement("BODY");

	// - property: altitude 
	tinyxml2::XMLElement* Pr_Altitude = El_Body->FirstChildElement("Altitude");
	int iVal = 0;
	Pr_Altitude->QueryIntText(&iVal);
	m_altitude = iVal;
}


void CSector::DebugBillet01(void)
{
	// > Set  Value
	m_altitude = 5;

	// > Save
	Save();
}
