#include "pch.h"
#include "CBat.h"
#include "CCollider.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CEventMgr.h"
#include "CSound.h"

CBat::CBat()
{
	m_iDir = -1;
	m_fSpeed = 50.0f;
	GetRigidBody()->EnableGravity(false);

	CTexture* pTexRight = CResMgr::GetInst()->LoadTexture(L"BatRight", L"Image\\Bat.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTexture(L"BatLeft", L"Image\\Bat_Left.bmp");

	CreateAnimator();
	CAnimator* pAnimator = GetAnimator();
	pAnimator->CreateAnimation(true, L"BatIdleRight", pTexRight, 5, 5, 0, 0, Vector2D(128.f, 128.f), .1f, 4);
	pAnimator->CreateAnimation(false, L"BatIdleLeft", pTexLeft, 5, 5, 0, 0, Vector2D(128.f, 128.f), .1f, 4);
	pAnimator->CreateAnimation(true, L"BatDieRight", pTexRight, 5, 5, 2, 3, Vector2D(128.f, 128.f), .15f, 11);
	pAnimator->CreateAnimation(false, L"BatDieLeft", pTexLeft, 5, 5, 2, 3, Vector2D(128.f, 128.f), .15f, 11);

	pAnimator->Play(L"BatIdleLeft", true);

	GetCollider()->SetScale(Vector2D(25.0f, 25.0f));
	m_pHitSound = CResMgr::GetInst()->LoadSound(L"HitSound", L"Sound\\EnemyHit.wav");

}

CBat::~CBat()
{
	
}

void CBat::Start()
{
	
}

void CBat::ChangeDirection()
{
	if (IsDead())return;
	if (GetCollider()->GetICol())
		m_iDir *= -1;
}

void CBat::Move()
{
	Vector2D vPos = GetPos();
	vPos.x += m_iDir * m_fSpeed * fDT;
	SetPos(vPos);
}

void CBat::UpdateAnim()
{
	if (IsDead())return;
	if (m_iDir == 1)
		GetAnimator()->Play(L"BatIdleRight", true);
	else
		GetAnimator()->Play(L"BatIdleLeft", true);
}



void CBat::Update()
{
	ChangeDirection();
	Move();
	Remove();
	UpdateAnim();

}

void CBat::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CBat::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	if (L"Player" == pObj->GetName())
	{
		tEvent eve = {};
		eve.eEven = EVENT_TYPE::PLAYER_HIT;
		CEventMgr::GetInst()->AddEvent(eve);
	}
}

void CBat::Hit()
{
	SetDead(true);
	if (m_iDir == 1)
		GetAnimator()->Play(L"BatDieRight", false);
	else
		GetAnimator()->Play(L"BatDieLeft", false);
	GetRigidBody()->EnableGravity(true);
	GetRigidBody()->SetVelocity(Vector2D(0.f, -150.f));
	m_pHitSound->Play(false);

}
