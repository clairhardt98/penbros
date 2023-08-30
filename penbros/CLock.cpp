#include "pch.h"
#include "CLock.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CEventMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CSound.h"

CLock::CLock()
	:m_bIsOpened(false)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2D(50.0f,50.0f));

	CreateAnimator();
	m_pIdleTex = CResMgr::GetInst()->LoadTexture(L"LockIdle", L"Image\\Lock_Idle.bmp");
	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"LockOpen", L"Image\\Lock.bmp");
	GetAnimator()->CreateAnimation(true, L"LockOpenAnim", m_pTex, 5, 6, 0, 0, Vector2D(64.f, 64.f), 0.1f, 30);
	m_pOpenLockSound = CResMgr::GetInst()->LoadSound(L"OpenLock", L"Sound\\OpenLock.wav");
}

CLock::~CLock()
{

}

void CLock::Update()
{
}

void CLock::Render(HDC _dc)
{
	Vector2D vPos = GetPos();
	Vector2D vScale = GetScale();
	if (!m_bIsOpened)
		TransparentBlt(_dc,
			(int)(vPos.x - vScale.x / 2.f),
			(int)(vPos.y - vScale.y / 2.f),
			(int)vScale.x,
			(int)vScale.y,
			m_pIdleTex->GetDC(),
			0, 0,
			(int)vScale.x,
			(int)vScale.y,
			RGB(255, 0, 255));
	else
	{
		ComponentRender(_dc);
	}
}

void CLock::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	if (L"Player" == pObj->GetName())
	{
		CPlayer* pPlayer = (CPlayer*)pObj;
		if (!pPlayer->HasKey())return;
		//printf("Stage Clear!\n");
		m_bIsOpened = true;
		m_pOpenLockSound->Play(false);
		GetAnimator()->Play(L"LockOpenAnim", true);
		tEvent eve = {};
		eve.eEven = EVENT_TYPE::STAGE_CLEAR;
		CEventMgr::GetInst()->AddEvent(eve);
	}
}




