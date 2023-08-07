#include "pch.h"
#include "CPlayer.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"

CPlayer::CPlayer()
	:m_pTex(nullptr)
{
	//리소스 매니저를 통한 리소스 로딩
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"Image\\Ball.bmp");
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2D(0.0f, 0.0f));
	GetCollider()->SetScale(Vector2D(25.0f, 25.0f));
}

CPlayer::~CPlayer()
{

}
void CPlayer::Update()
{
	Vector2D vPos = GetPos();
	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.0f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.0f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.0f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.0f * fDT;
	}

	SetPos(vPos);
}

void CPlayer::Render(HDC _dc)
{
	//음수 좌표에도 표현할 수 있도록 int로 받는다
	int iWidth = m_pTex->Width();
	int iHeight = m_pTex->Height();

	Vector2D vPos = GetPos();
	//좌 상단 x
	
	/*BitBlt(_dc
			, int(vPos.x - (float)(iWidth / 2))
			, int(vPos.y - (float)(iHeight / 2))
			, iWidth, iHeight
			, m_pTex->GetDC()
			,0,0,SRCCOPY);*/

	TransparentBlt(_dc
			, int(vPos.x - (float)(iWidth / 2))
			, int(vPos.y - (float)(iHeight / 2))
			, iWidth, iHeight
			, m_pTex->GetDC()
			, 0, 0, iWidth, iHeight
			, RGB(255, 0, 255));

	//컴포넌트(충돌체, etc...) 렌더
	ComponentRender(_dc);
}


