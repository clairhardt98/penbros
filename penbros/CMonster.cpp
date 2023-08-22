#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CResMgr.h"

CMonster::CMonster()
	:m_fSpeed(100.0f)
	,m_iDir(1)
{
	CreateCollider();
	CreateRigidBody();
	
}

CMonster::~CMonster()
{
}

void CMonster::Update()
{
	
}


