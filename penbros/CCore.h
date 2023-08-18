#pragma once

class CCore
{
	SINGLE(CCore);
private:
	HWND	m_hWnd;			//메인 윈도우 핸들
	POINT	m_ptResolution;	//메인 윈도우 해상도
	HDC		m_hdc;			//메인 윈도우에 Draw할 DC

	HBITMAP m_hBit;
	HDC		m_memDC;

	//자주 사용하는 펜
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	//gdi+
	ULONG_PTR gdiplusToken;
	Gdiplus::Graphics* m_gGraphics;

public:
	int Init(HWND hWnd, POINT res);
	void Progress();
private:
	void CreateBrushPen();
	

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC GetMainDC() { return m_hdc; }
	Gdiplus::Graphics* GetGraphics() { return m_gGraphics; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};

