// WastGDIDraw.c
// implementation file
//
// *** plans TODO: ***
// 09.02.20
// - [09.02.20] draw Grid (main level0 grid)
// - [09.02.20] load Grid from file.xml
// - [09.02.20] find a concept to separate graphic engine from Wast-project core logic
// - [09.02.20] save Grid to file.xml


#include "WastGDIDraw.h"


////////////////////////////////////////////////////////////
// class WastGDIDraw
////////////////////////////////////////////////////////////
WastGDIDraw::WastGDIDraw()
{
	// defaults
	m_hWnd = 0;

	m_canvasRect.bottom = 0;
	m_canvasRect.left = 0;
	m_canvasRect.right = 0;
	m_canvasRect.top = 0;
}


WastGDIDraw::WastGDIDraw(HWND hWnd)
{
	// set up 
	m_hWnd = hWnd;

	GetClientRect(m_hWnd, &m_canvasRect);
}


WastGDIDraw::~WastGDIDraw()
{

}


void WastGDIDraw::Init(HWND hWnd)
{
	// set up window values
	m_hWnd = hWnd;

	GetClientRect(m_hWnd, &m_canvasRect);
}


void WastGDIDraw::DrawPixels()
{
	PAINTSTRUCT ps;

	if (m_canvasRect.bottom == 0) {

		return;
	}

	HDC hdc = BeginPaint(m_hWnd, &ps);

	for (int i = 0; i < 1000; i++) {

		int x = rand() % m_canvasRect.right;
		int y = rand() % m_canvasRect.bottom;
		SetPixel(hdc, x, y, RGB(255, 0, 0));
	}

	EndPaint(m_hWnd, &ps);
}