#pragma once

class CCore
{
	SINGLE(CCore);
private:
	HWND	m_hWnd;			//���� ������ �ڵ�
	POINT	m_ptResolution;	//���� ������ �ػ�
	HDC		m_hdc;			//���� �����쿡 Draw�� DC

	HBITMAP m_hBit;
	HDC		m_memDC;

	//���� ����ϴ� ��
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

