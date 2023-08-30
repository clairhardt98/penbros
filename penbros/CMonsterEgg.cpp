#include "pch.h"
#include "CMonsterEgg.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CBat.h"
#include "CCrab.h"
#include "CRat.h"

CMonsterEgg::CMonsterEgg()
	:m_strMonsterType(L"")
	, m_vTargetPos(Vector2D(0.f, 0.f))
	, m_bIsArrived(false)
	, m_iTargetDir(1)
{
	CreateAnimator();
	CTexture* pTexIdle = CResMgr::GetInst()->LoadTexture(L"MonsterEggIdle", L"Image\\EggIdle.bmp");
	CTexture* pTexAnim = CResMgr::GetInst()->LoadTexture(L"MonsterEgg", L"Image\\Egg.bmp");
	
	GetAnimator()->CreateAnimation(true, L"MonsterEggIdle", pTexIdle, 1, 1, 0, 0, Vector2D(75.0f, 75.0f), 0.5f, 1);
	GetAnimator()->CreateAnimation(true, L"MonsterEggAnim", pTexAnim, 1, 5, 0, 0, Vector2D(75.0f, 75.0f), 0.2f, 5);
	GetAnimator()->Play(L"MonsterEggIdle", true);
	CreateRigidBody();
	GetRigidBody()->SetVelocity(Vector2D(0.f, 2000.0f));
}

CMonsterEgg::~CMonsterEgg()
{
}


void CMonsterEgg::Update()
{
	UpdateAnim();

	if (m_bIsArrived)
	{
		if (GetAnimator()->GetCurAnimation()->IsFinish())
		{
			SpawnMonster();
		}
	}

	if (!m_bIsArrived && abs(GetPos().y - m_vTargetPos.y) < 1.f)
	{
		m_bIsArrived = true;
		GetRigidBody()->SetVelocity(Vector2D(0.f, 0.0f));
	}
}

void CMonsterEgg::Render(HDC _dc)
{

	Vector2D vPos = GetPos();
	Vector2D vScale = GetScale();
	ComponentRender(_dc);
}

void CMonsterEgg::UpdateAnim()
{
	if (!m_bIsArrived)
	{
		GetAnimator()->Play(L"MonsterEggIdle", true);
	}
	else
	{
		GetAnimator()->Play(L"MonsterEggAnim", false);
	}
}
void CMonsterEgg::SpawnMonster()
{
	if (L"Bat" == m_strMonsterType)
	{
		CObject* pBat = new CBat;
		pBat->SetName(L"Monster");
		pBat->SetPos(m_vTargetPos);
		pBat->SetScale(Vector2D(40.0f, 40.0f));
		CBat* temp = (CBat*)pBat;
		temp->SetDirection(m_iTargetDir);
		CreateObject(pBat, GROUP_TYPE::MONSTER);
	}
	if (L"Crab" == m_strMonsterType)
	{
		CObject* pCrab = new CCrab;
		pCrab->SetName(L"Monster");
		pCrab->SetPos(m_vTargetPos);
		pCrab->SetScale(Vector2D(40.0f, 40.0f));
		CCrab* temp = (CCrab*)pCrab;
		temp->SetDirection(m_iTargetDir);
		CreateObject(pCrab, GROUP_TYPE::MONSTER);
	}

	if (L"Rat" == m_strMonsterType)
	{
		CObject* pRat = new CRat;
		pRat->SetName(L"Monster");
		pRat->SetPos(m_vTargetPos);
		pRat->SetScale(Vector2D(40.0f, 40.0f));
		CRat* temp = (CRat*)pRat;
		temp->SetDirection(m_iTargetDir);
		CreateObject(pRat, GROUP_TYPE::MONSTER);
	}
	DeleteObject(this);
}

