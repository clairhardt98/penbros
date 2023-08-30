#include "pch.h"
#include "CScene_End.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CSound.h"
#include "CImage.h"
#include "CCore.h"
#include "CPathMgr.h"

CScene_End::CScene_End()
{
	//���� �ε�
	m_pBGSound = CResMgr::GetInst()->LoadSound(L"EndingBgm", L"Sound\\Ending.wav");
	//�̹��� �ε�
	m_pBGTex = CResMgr::GetInst()->LoadTexture(L"TitleBGEnd", L"Image\\End.bmp");

	wstring linePath = L"Image\\ThankYouForPlaying.png";
	wstring imgPath = CPathMgr::GetInst()->GetContentPath() + linePath;
	m_pTitleLineImg = new Gdiplus::Image(imgPath.c_str());
	m_pGr = new Gdiplus::Graphics(CCore::GetInst()->GetMemDC());
}

CScene_End::~CScene_End()
{

	if(nullptr!= m_pTitleLineImg)
		delete m_pTitleLineImg;
	if(nullptr!=m_pGr)
		delete m_pGr;
}

void CScene_End::Update()
{
	CScene::Update();
	if (KEY_TAP(KEY::ENTER))
	{
		PostQuitMessage(0);
	}
}

void CScene_End::Render(HDC _dc)
{
	using namespace Gdiplus;
	//��� �̹���
	BitBlt(_dc, 0, 0, 800, 600, m_pBGTex->GetDC(), 0, 0, SRCCOPY);
	//Ÿ��Ʋ gdi+

	int w = m_pTitleLineImg->GetWidth();
	int h = m_pTitleLineImg->GetHeight();
	m_pGr->DrawImage(m_pTitleLineImg, 400 - w / 2, 250 - h / 2);
}

void CScene_End::Enter()
{
	CSoundMgr::GetInst()->RegisterToBGM(m_pBGSound);
	m_pBGSound->PlayToBGM(true);

}

void CScene_End::Exit()
{
}
