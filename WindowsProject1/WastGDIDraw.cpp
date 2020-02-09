// WastGDIDraw.c
// implementation file

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