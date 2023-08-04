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


public:
	int Init(HWND hWnd, POINT res);
	void Progress();
private:
	

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC GetMainDC() { return m_hdc; }
};

