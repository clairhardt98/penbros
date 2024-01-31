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

public:
	int Init(HWND hWnd, POINT res);
	void Progress();
private:
	void CreateBrushPen();


public:
	HWND GetMainHwnd() const { return m_hWnd; }
	POINT GetResolution() const { return m_ptResolution; }
	HDC GetMainDC() const { return m_hdc; }
	HDC GetMemDC() const { return m_memDC; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) const { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) const { return m_arrPen[(UINT)_eType]; }
};

