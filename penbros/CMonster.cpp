#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CResMgr.h"
#include "CCore.h"

CMonster::CMonster()
	:m_fSpeed(100.0f)
	,m_iDir(1)
	,m_bDead(false)
{
	CreateCollider();
	CreateRigidBody();
}

CMonster::~CMonster()
{
}

void CMonster::SetDead(bool _b)
{
	m_bDead = _b;
	m_fSpeed = 0.f;
	if (m_bDead)
		SetName(L"DeadMonster");
}

void CMonster::Remove()
{
	if (m_bDead && GetPos().y > CCore::GetInst()->GetResolution().y + 50.f)
		DeleteObject(this);
}

void CMonster::Update()
{
	
}


