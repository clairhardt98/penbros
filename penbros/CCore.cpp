#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"


//objects

HBITMAP hBitmap;
BITMAP BitBack;


CCore::CCore()
	:m_hWnd(0)
	, m_ptResolution{}
	, m_hdc(0)
	, m_hBit(0)
	, m_memDC(0)

{}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hdc);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::Init(HWND hWnd, POINT res)
{
	this->m_hWnd = hWnd;
	this->m_ptResolution = res;

	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(hWnd, nullptr, 600, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hdc = GetDC(hWnd);

	//이중 버퍼링
	m_hBit = CreateCompatibleBitmap(m_hdc, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hdc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);
	//Init Mgr
	CTimeMgr::GetInst()->Init();
	CPathMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();
	
	return S_OK;
}

void CCore::Progress()
{
	CTimeMgr::GetInst()->Update();
	CKeyMgr::GetInst()->Update();
	CTimeMgr::GetInst()->Render();
	CSceneMgr::GetInst()->Update();
	
	//>>
	//Rendering
	//<<
	//화면 clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	CSceneMgr::GetInst()->Render(m_memDC);

	BitBlt(m_hdc, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}

