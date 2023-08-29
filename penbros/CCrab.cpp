#include "pch.h"
#include "CCrab.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CRigidBody.h"
#include "CCrabProjectile.h"

CCrab::CCrab()
	:m_iDir(1)
	,m_eCurState(CRAB_STATE::IDLE)
	,m_ePrevState(CRAB_STATE::START)
	,m_bIsAttacking(false)
	,m_fDetectionDist(250.0f)
{
	CTexture* pTexRight = CResMgr::GetInst()->LoadTexture(L"CrabRight", L"Image\\Crab.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTexture(L"CrabLeft", L"Image\\Crab_Left.bmp");

	CreateAnimator();
	CAnimator* pAnimator = GetAnimator();
	pAnimator->CreateAnimation(true, L"CrabIdleRight", pTexRight, 7, 7, 0, 0, Vector2D(128.f, 128.f), .2f, 4);
	pAnimator->CreateAnimation(false, L"CrabIdleLeft", pTexLeft, 7, 7, 0, 0, Vector2D(128.f, 128.f), .2f, 4);
	pAnimator->CreateAnimation(true, L"CrabAttackRight", pTexRight, 7, 7, 2, 3, Vector2D(128.f, 128.f), .1f, 10);
	pAnimator->CreateAnimation(false, L"CrabAttackLeft", pTexLeft, 7, 7, 2, 3, Vector2D(128.f, 128.f), .1f, 10);
	pAnimator->CreateAnimation(true, L"CrabDieRight", pTexRight, 7, 7, 6, 0, Vector2D(128.f, 128.f), .2f, 5);
	pAnimator->CreateAnimation(false, L"CrabDieLeft", pTexLeft, 7, 7, 6, 0, Vector2D(128.f, 128.f), .2f, 5);

	CAnimation* pAniIdleRight = pAnimator->FindAnimation(L"CrabIdleRight");
	CAnimation* pAniIdleLeft = pAnimator->FindAnimation(L"CrabIdleLeft");
	CAnimation* pAniAttackRight = pAnimator->FindAnimation(L"CrabAttackRight");
	CAnimation* pAniAttackLeft = pAnimator->FindAnimation(L"CrabAttackLeft");
	CAnimation* pAniDieRight = pAnimator->FindAnimation(L"CrabDieRight");
	CAnimation* pAniDieLeft = pAnimator->FindAnimation(L"CrabDieLeft");
	
	//8프레임 째에 이벤트 발생하게 함
	//이 이벤트는 fire 함수를 호출함
	pAniAttackRight->SetEventFrame(6);
	pAniAttackLeft->SetEventFrame(6);
	for (int i = 0; i < pAniIdleRight->GetMaxFrame(); i++)
		pAniIdleRight->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAniIdleLeft->GetMaxFrame(); i++)
		pAniIdleLeft->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAniAttackRight->GetMaxFrame(); i++)
		pAniAttackRight->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAniAttackLeft->GetMaxFrame(); i++)
		pAniAttackLeft->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAniDieRight->GetMaxFrame(); i++)
		pAniDieRight->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAniDieLeft->GetMaxFrame(); i++)
		pAniDieLeft->GetFrame(i).vOffset = Vector2D(0.f, -15.f);

	GetCollider()->SetScale(Vector2D(25.0f, 25.0f));

	GetRigidBody()->EnableGravity(true);
}

CCrab::~CCrab()
{
}



void CCrab::UpdateAnim()
{
	if (IsDead() || m_eCurState == m_ePrevState)return;
	switch (m_eCurState)
	{
	case CRAB_STATE::IDLE:
		//그냥 애니메이션만 출력하자
	{
		CAnimation* pAniAttackRight = GetAnimator()->FindAnimation(L"CrabAttackRight");
		CAnimation* pAniAttackLeft = GetAnimator()->FindAnimation(L"CrabAttackLeft");
		pAniAttackRight->SetFrame(0);
		pAniAttackLeft->SetFrame(0);
		if (m_iDir == 1)
			GetAnimator()->Play(L"CrabIdleRight", true);
		else
			GetAnimator()->Play(L"CrabIdleLeft", true);
		break;
	}
	case CRAB_STATE::ATTACK:
		//공격 애니메이션 반복 출력
		if (m_iDir == 1)
			GetAnimator()->Play(L"CrabAttackRight", true);
		else
			GetAnimator()->Play(L"CrabAttackLeft", true);
		break;
	case CRAB_STATE::DIE:
		//죽는 애니메이션 실행
		if (m_iDir == 1)
			GetAnimator()->Play(L"CrabDieRight", false);
		else
			GetAnimator()->Play(L"CrabDieLeft", false);
		break;
	}
}

void CCrab::UpdateState()
{
	//현재 위치와 플레이어와의 거리를 판단해서 ATTACK 스테이트로 변경
	m_ePrevState = m_eCurState;

	if (IsDead())
	{
		m_eCurState = CRAB_STATE::DIE;
		
		return;
	}
	if (CanAttack())
	{
		m_eCurState = CRAB_STATE::ATTACK;
		m_bIsAttacking = true;
	}
	else
	{
		m_eCurState = CRAB_STATE::IDLE;
		m_bIsAttacking = false;
	}
}

bool CCrab::CanAttack()
{
	CObject* pPlayer = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	if (nullptr == pPlayer)return false;
	Vector2D vPlayerPos = pPlayer->GetPos();
	
	Vector2D vPos = GetPos();
	if (abs(vPlayerPos.y - vPos.y) > 30.f)return false;
	if (m_iDir == -1 && vPos.x - vPlayerPos.x < m_fDetectionDist)
		return true;
	
	if (m_iDir == 1 && vPlayerPos.x - vPos.x < m_fDetectionDist)
		return true;

	return false;
}

void CCrab::Fire()
{
	CCrabProjectile* pProj = new CCrabProjectile;
	pProj->SetPos(Vector2D(GetPos().x + 10 * m_iDir, GetPos().y - 10.f));
	pProj->SetScale(Vector2D(17.f, 10.f));
	pProj->SetDirection(m_iDir);
	pProj->GetRigidBody()->SetVelocity(Vector2D(300.0f * m_iDir, 0.f));
	CreateObject(pProj, GROUP_TYPE::MONSTERPROJ);
}

void CCrab::Start()
{
	if (m_iDir == 1)
		GetAnimator()->Play(L"CrabIdleRight", true);
	else
		GetAnimator()->Play(L"CrabIdleLeft", true);
}

void CCrab::Update()
{
	Remove();
	UpdateAnim();
	UpdateState();
	
	
	/*if (m_bIsAttacking && GetAnimator()->GetCurAnimation()->IsFinish())
		Fire();*/
	
}

void CCrab::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CCrab::OnCollisionEnter(CCollider* _pOther)
{
}

void CCrab::Hit()
{
	SetDead(true);
	if (m_iDir == 1)
		GetAnimator()->Play(L"CrabDieRight", false);
	else
		GetAnimator()->Play(L"CrabDieLeft", false);
	GetRigidBody()->EnableGravity(true);
	GetRigidBody()->SetVelocity(Vector2D(0.f, -150.f));
}

void CCrab::OnAnimEvent()
{
	Fire();
}



