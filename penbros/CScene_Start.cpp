#include "pch.h"
#include "CScene_Start.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CSound.h"
#include "CImage.h"
#include "CCore.h"
#include "CPathMgr.h"

CScene_Start::CScene_Start()
{
	//���� �ε�
	m_pBGSound = CResMgr::GetInst()->LoadSound(L"TitleBgm", L"Sound\\title.wav");
	//�̹��� �ε�
	m_pBGTex = CResMgr::GetInst()->LoadTexture(L"TitleBG", L"Image\\TitleBG.bmp");
	//���� ���
	//bgm���δٰ� ���
	//Ÿ��Ʋ �̹��� �ε�
	wstring titlePath = L"Image\\Title.png";
	wstring imgPath = CPathMgr::GetInst()->GetContentPath() + titlePath;
	m_pTitleImg = new Gdiplus::Image(imgPath.c_str());

	wstring linePath = L"Image\\PressEnterToContinue.png";
	imgPath = CPathMgr::GetInst()->GetContentPath() + linePath;
	m_pTitleLineImg = new Gdiplus::Image(imgPath.c_str());
	m_pGr = new Gdiplus::Graphics(CCore::GetInst()->GetMemDC());
}

CScene_Start::~CScene_Start()
{
	if(nullptr!=m_pTitleImg)
		delete m_pTitleImg;
	if (nullptr != m_pTitleLineImg)
		delete m_pTitleLineImg;
	if (nullptr != m_pGr)
		delete m_pGr;
}

void CScene_Start::Update()
{
	CScene::Update();
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::STAGE_01);
	}
}

void CScene_Start::Render(HDC _dc)
{
	using namespace Gdiplus;
	//��� �̹���
	BitBlt(_dc, 0, 0, 800, 600, m_pBGTex->GetDC(), 0, 0, SRCCOPY);
	//Ÿ��Ʋ gdi+
	Vector2D vPos = Vector2D(400.0f, 300.0f);
	int w = m_pTitleImg->GetWidth();
	int h = m_pTitleImg->GetHeight();

	m_pGr->DrawImage(m_pTitleImg,400-w/2,300-h/2);
	w = m_pTitleLineImg->GetWidth();
	h = m_pTitleLineImg->GetHeight();
	m_pGr->DrawImage(m_pTitleLineImg, 400 - w / 2, 450 - h / 2);
}

void CScene_Start::Enter()
{
	CSoundMgr::GetInst()->RegisterToBGM(m_pBGSound);
	m_pBGSound->PlayToBGM(true);

}

void CScene_Start::Exit()
{
}
