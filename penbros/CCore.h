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


public:
	int Init(HWND hWnd, POINT res);
	void Progress();
private:
	

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC GetMainDC() { return m_hdc; }
};

