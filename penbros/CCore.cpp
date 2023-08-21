#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"


//objects

HBITMAP hBitmap;
BITMAP BitBack;


CCore::CCore()
	:m_hWnd(0)
	, m_ptResolution{}
	, m_hdc(0)
	, m_hBit(0)
	, m_memDC(0)
	, gdiplusToken(0)
{}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hdc);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (size_t i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
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
	//자주 사용할 펜과 브러시 생성
	CreateBrushPen();

	// >>gdi+ init
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	// <<
	
	//Init Mgr
	CTimeMgr::GetInst()->Init();
	CPathMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();
	CCollisionMgr::GetInst()->Init();

	return S_OK;
}

void CCore::Progress()
{
	//mgr update
	CTimeMgr::GetInst()->Update();
	CKeyMgr::GetInst()->Update();

	//Scene update
	CSceneMgr::GetInst()->Update();

	//collision check
	CCollisionMgr::GetInst()->Update();//충돌 검사 해준 후 렌더링으로 넘어가기

	//>>
	//Rendering
	//<<
	//화면 clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	CSceneMgr::GetInst()->Render(m_memDC);

	BitBlt(m_hdc, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
	CTimeMgr::GetInst()->Render();

	//이벤트 지연처리
	CEventMgr::GetInst()->Update();

}

void CCore::CreateBrushPen()
{
	//hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] =
		(HBRUSH)GetStockObject(HOLLOW_BRUSH);//이미 Stock 오브젝트로 존재, delete 필요 없음

	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

