#include "pch.h"
#include "CGhost.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"
#include "CEventMgr.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CSound.h"

CGhost::CGhost()
	:m_pTarget(nullptr)
	,m_fSpeed(50.f)
	,m_iDir(1)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2D(0.0f, 0.0f));
	GetCollider()->SetScale(Vector2D(25.0f, 25.0f));

	CreateRigidBody();
	GetRigidBody()->EnableGravity(false);

	CTexture* pTexRight = CResMgr::GetInst()->LoadTexture(L"GhostRight", L"Image\\Ghost.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTexture(L"GhostLeft", L"Image\\Ghost_Left.bmp");

	CreateAnimator();
	CAnimator* pAnimator = GetAnimator();
	pAnimator->CreateAnimation(true, L"GhostIdleRight", pTexRight, 1, 8, 0, 0, Vector2D(54.f, 58.f), .2f, 8);
	pAnimator->CreateAnimation(false, L"GhostIdleLeft", pTexLeft, 1, 8, 0, 0, Vector2D(54.f, 58.f), .2f, 8);

	m_pSound = CResMgr::GetInst()->LoadSound(L"Ghost", L"Sound\\Ghost.wav");
	m_pSound->Play(false);
}

CGhost::~CGhost()
{
}


void CGhost::Trace(Vector2D _vTarget)
{
	Vector2D vPos = GetPos();
	Vector2D vDir = _vTarget - vPos;
	if (vDir.x <= 0)
		m_iDir = 1;
	else
		m_iDir = -1;
	vDir.normalize();
	vPos += vDir * m_fSpeed * fDT;
	SetPos(vPos);
}

void CGhost::UpdateAnim()
{
	if (m_iDir == 1)
		GetAnimator()->Play(L"GhostIdleRight",true);
	else
		GetAnimator()->Play(L"GhostIdleLeft", true);
}

void CGhost::Update()
{
	UpdateAnim();
	m_pTarget = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	//플레이어 따라가는 로직
	if (nullptr != m_pTarget)
	{
		Vector2D vTargetPos = m_pTarget->GetPos();
		Trace(vTargetPos);
	}
	else
	{
		Vector2D vTargetPos = Vector2D(400.f, 300.f);
		Trace(vTargetPos);
	}
}

void CGhost::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CGhost::OnCollisionEnter(CCollider* _pOther)
{
	//PlayerHit 이벤트 발생
	CObject* pObj = _pOther->GetObj();
	if (pObj->GetName() == m_pTarget->GetName())
	{
		tEvent eve = {};
		eve.eEven = EVENT_TYPE::PLAYER_HIT;
		CEventMgr::GetInst()->AddEvent(eve);
	}
}

