#include "pch.h"
#include "CRat.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CSound.h"

CRat::CRat()
	:m_iDir(1)
	, m_eCurState(RAT_STATE::IDLE)
	, m_ePrevState(RAT_STATE::START)
	, m_bIsAttacking(false)
	, m_fDetectionDist(250.0f)
{
	m_fSpeed = 100.0f;
	CTexture* pTexRight = CResMgr::GetInst()->LoadTexture(L"RatRight", L"Image\\Rat.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTexture(L"RatLeft", L"Image\\Rat_Left.bmp");

	CreateAnimator();
	CAnimator* pAnimator = GetAnimator();
	pAnimator->CreateAnimation(true, L"RatIdleRight", pTexRight, 6, 6, 0, 0, Vector2D(128.f, 128.f), .2f, 4);
	pAnimator->CreateAnimation(false, L"RatIdleLeft", pTexLeft, 6, 6, 0, 0, Vector2D(128.f, 128.f), .2f, 4);
	pAnimator->CreateAnimation(true, L"RatWaitRight", pTexRight, 6, 6, 0, 4, Vector2D(128.f, 128.f), .1f, 6);
	pAnimator->CreateAnimation(false, L"RatWaitLeft", pTexLeft, 6, 6, 0, 4, Vector2D(128.f, 128.f), .1f, 6);
	pAnimator->CreateAnimation(true, L"RatAttackRight", pTexRight, 6, 6, 1, 4, Vector2D(128.f, 128.f), .1f, 8);
	pAnimator->CreateAnimation(false, L"RatAttackLeft", pTexLeft, 6, 6, 1, 4, Vector2D(128.f, 128.f), .1f, 8);
	pAnimator->CreateAnimation(true, L"RatDieRight", pTexRight, 6, 6, 4, 5, Vector2D(128.f, 128.f), .2f, 5);
	pAnimator->CreateAnimation(false, L"RatDieLeft", pTexLeft, 6, 6, 4, 5, Vector2D(128.f, 128.f), .2f, 5);

	CAnimation* pAniIdleRight = pAnimator->FindAnimation(L"RatIdleRight");
	CAnimation* pAniIdleLeft = pAnimator->FindAnimation(L"RatIdleLeft");
	CAnimation* pAniWaitRight = pAnimator->FindAnimation(L"RatWaitRight");
	CAnimation* pAniWaitLeft = pAnimator->FindAnimation(L"RatWaitLeft");
	CAnimation* pAniAttackRight = pAnimator->FindAnimation(L"RatAttackRight");
	CAnimation* pAniAttackLeft = pAnimator->FindAnimation(L"RatAttackLeft");
	CAnimation* pAniDieRight = pAnimator->FindAnimation(L"RatDieRight");
	CAnimation* pAniDieLeft = pAnimator->FindAnimation(L"RatDieLeft");

	//wait 애니메이션이 끝나면 바로 Attack으로 넘어가게 하자

	for (int i = 0; i < pAniIdleRight->GetMaxFrame(); i++)
		pAniIdleRight->GetFrame(i).vOffset = Vector2D(0.f, -20.f);
	for (int i = 0; i < pAniIdleLeft->GetMaxFrame(); i++)
		pAniIdleLeft->GetFrame(i).vOffset = Vector2D(0.f, -20.f);
	for (int i = 0; i < pAniWaitRight->GetMaxFrame(); i++)
		pAniWaitRight->GetFrame(i).vOffset = Vector2D(0.f, -20.f);
	for (int i = 0; i < pAniWaitLeft->GetMaxFrame(); i++)
		pAniWaitLeft->GetFrame(i).vOffset = Vector2D(0.f, -20.f);
	for (int i = 0; i < pAniAttackRight->GetMaxFrame(); i++)
		pAniAttackRight->GetFrame(i).vOffset = Vector2D(0.f, -20.f);
	for (int i = 0; i < pAniAttackLeft->GetMaxFrame(); i++)
		pAniAttackLeft->GetFrame(i).vOffset = Vector2D(0.f, -20.f);
	for (int i = 0; i < pAniDieRight->GetMaxFrame(); i++)
		pAniDieRight->GetFrame(i).vOffset = Vector2D(0.f, -20.f);
	for (int i = 0; i < pAniDieLeft->GetMaxFrame(); i++)
		pAniDieLeft->GetFrame(i).vOffset = Vector2D(0.f, -20.f);

	GetCollider()->SetScale(Vector2D(25.0f, 25.0f));

	GetRigidBody()->EnableGravity(true);
	GetRigidBody()->SetFricCoeff(0.f);
	GetRigidBody()->SetMaxVelocity(Vector2D(50.0f, 1000.f));

	m_pHitSound = CResMgr::GetInst()->LoadSound(L"HitSound", L"Sound\\EnemyHit.wav");

}

CRat::~CRat()
{

}


void CRat::ChangeDirection()
{
	
	//하나 이상의 collider와의 충돌이 있다면 방향 바꾸기
	if (IsDead())return;
	GetRigidBody()->SetVelocity(Vector2D(0.f, 0.f));
	m_eCurState = RAT_STATE::IDLE;
	m_bIsAttacking = true;
	m_iDir *= -1;
	if (m_iDir == 1)
		GetAnimator()->Play(L"RatIdleRight", true);
	else
		GetAnimator()->Play(L"RatIdleLeft", true);
	GetRigidBody()->SetMaxVelocity(Vector2D(50.0f, 1000.f));

}

void CRat::Move()
{
	if(m_bIsAttacking)
		GetRigidBody()->AddForce(Vector2D(250.0f * m_iDir, 0.f));
	else
		GetRigidBody()->AddForce(Vector2D(50.0f * m_iDir, 0.f));

}

void CRat::UpdateAnim()
{
	if (IsDead() || (m_ePrevState == m_eCurState))return;
	switch (m_eCurState)
	{
	case RAT_STATE::IDLE:
		if (m_iDir == 1)
			GetAnimator()->Play(L"RatIdleRight", true);
		else
			GetAnimator()->Play(L"RatIdleLeft", true);
		break;
	case RAT_STATE::WAIT:
		if (m_iDir == 1)
			GetAnimator()->Play(L"RatWaitRight", false);
		else
			GetAnimator()->Play(L"RatWaitLeft", false);
		break;
	case RAT_STATE::ATTACK:
		if (m_iDir == 1)
			GetAnimator()->Play(L"RatAttackRight", true);
		else
			GetAnimator()->Play(L"RatAttackLeft", true);
		break;
	}

}

void CRat::UpdateState()
{
	if (IsDead())return;
	m_ePrevState = m_eCurState;
	//스테이트들 처리
	
	//공격 체크가 되면 Wait으로, Wait에서 공격할 수 없게 넘어가면 다시 IDLE로
	if (m_eCurState == RAT_STATE::IDLE)
	{
		GetAnimator()->FindAnimation(L"RatWaitRight")->SetFrame(0);
		GetAnimator()->FindAnimation(L"RatWaitLeft")->SetFrame(0);
		m_bIsAttacking = false;
	}
	if (m_ePrevState == RAT_STATE::IDLE && CanAttack())
	{
		GetRigidBody()->ResetAccel();
		GetRigidBody()->SetVelocity(Vector2D(0.0f, 0.0f));
		m_eCurState = RAT_STATE::WAIT;
	}
	if (m_ePrevState == RAT_STATE::WAIT && !CanAttack())
	{
		m_bIsAttacking = false;
		GetRigidBody()->SetMaxVelocity(Vector2D(150.0f, 1000.f));
		m_eCurState = RAT_STATE::IDLE;
	}
	//Wait상태이고, 공격할 수 있다면, WAIt애니메이션이 끝나면 STATE를 ATTACK으로
	if (m_ePrevState == RAT_STATE::WAIT && CanAttack())
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			m_bIsAttacking = true;
			GetRigidBody()->SetMaxVelocity(Vector2D(300.0f, 1000.f));
			m_eCurState = RAT_STATE::ATTACK;
		}
	}
}

bool CRat::CanAttack()
{
	CObject* pPlayer = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	if (nullptr == pPlayer)return false;
	Vector2D vPlayerPos = pPlayer->GetPos();

	Vector2D vPos = GetPos();
	if (abs(vPlayerPos.y - vPos.y) > 30.f)return false;
	if (m_iDir == -1 && vPos.x > vPlayerPos.x && vPos.x - vPlayerPos.x < m_fDetectionDist)
		return true;

	if (m_iDir == 1 && vPlayerPos.x > vPos.x && vPos.x - vPlayerPos.x < m_fDetectionDist)
		return true;

	return false;
}

void CRat::Start()
{
}

void CRat::Update()
{
	Remove();
	m_iPrevDir = m_iDir;
	Move();

	UpdateAnim();
	UpdateState();
}

void CRat::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CRat::Hit()
{
	SetDead(true);
	if (m_iDir == 1)
		GetAnimator()->Play(L"RatDieRight", false);
	else
		GetAnimator()->Play(L"RatDieLeft", false);
	GetRigidBody()->EnableGravity(true);
	GetRigidBody()->SetVelocity(Vector2D(0.f, -150.f));
	m_pHitSound->Play(false);
}

void CRat::OnCollisionEnter(CCollider* _pOther)
{
	//벽에 닿으면 방향 바꾸기
	CObject* pObj = _pOther->GetObj();
	if (L"Wall" == pObj->GetName())
		ChangeDirection();

	if (m_bIsAttacking)
	{
		CObject* pObj = _pOther->GetObj();
		if (L"Player" == pObj->GetName())
		{
			tEvent eve = {};
			eve.eEven = EVENT_TYPE::PLAYER_HIT;
			CEventMgr::GetInst()->AddEvent(eve);
		}
	}
}

