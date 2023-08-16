#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CResMgr.h"

CMonster::CMonster()
	:m_vCenterPos(Vector2D(0.0f, 0.0f))
	,m_fSpeed(100.0f)
	,m_fMaxDistance(50.0f)
	,m_iDir(1)
	,m_iHP(5)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2D(45.0f, 45.0f));
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"EnemyTex_Bat", L"Image\\Bat.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(true, L"BAT_IDLE", pTex, 5, 5, 0, 0, Vector2D(128.0f, 128.0f), 0.1f, 4);
	GetAnimator()->Play(L"BAT_IDLE", true);
}

CMonster::~CMonster()
{
}

void CMonster::Update()
{
	Vector2D vCurPos = GetPos();

	//진행 방향으로 시간당 m_fSpeed만큼 이동

	vCurPos.x += fDT * m_fSpeed * m_iDir;

	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance; // 초과량

	if (0.0f < fDist)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;//dt동안 초과한 양 만큼 다시 반대방향으로 움직여준다
	}
	SetPos(vCurPos);
	m_vCenterPos;
}

void CMonster::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	//몬스터 본인이 충돌 시 일어날 일
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_iHP -= 1;
		if (m_iHP <= 0)
			DeleteObject(this);
	}
	
}