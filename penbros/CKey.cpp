#include "pch.h"
#include "CKey.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CEventMgr.h"
#include "CPlayer.h"
CKey::CKey()
	:m_pPlayer(nullptr)
	,m_bIsCaptured(false)
	,m_iDir(1)
	,m_pCurPlate(nullptr)
	,m_vPrevPos(Vector2D(0.f,0.f))
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2D(0.0f, 0.0f));
	GetCollider()->SetScale(Vector2D(25.0f, 25.0f));

	CreateAnimator();

	CTexture* pTexRight = CResMgr::GetInst()->LoadTexture(L"KeyRight", L"Image\\Key.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTexture(L"KeyLeft", L"Image\\Key_Left.bmp");

	GetAnimator()->CreateAnimation(true, L"KeyRight", pTexRight, 4, 4, 0, 0, Vector2D(64.0f, 64.0f), 0.2f, 16);
	GetAnimator()->CreateAnimation(true, L"KeyLeft", pTexLeft, 4, 4, 0, 0, Vector2D(64.0f, 64.0f), 0.2f, 16);
	GetAnimator()->Play(L"KeyRight", true);
	CreateRigidBody();
	GetRigidBody()->EnableGravity(true);
}

CKey::~CKey()
{
}


void CKey::Update()
{
	UpdateAnim();
	if (m_bIsCaptured && nullptr != m_pPlayer)
	{
		Vector2D vPlayerPos = m_pPlayer->GetPos();
		m_iDir = m_pPlayer->GetDir();
		SetPos(Vector2D(vPlayerPos.x + 15.f * m_iDir, vPlayerPos.y - 20.f));
		m_vPrevPos = Vector2D(vPlayerPos.x + 15.f * m_iDir, vPlayerPos.y - 20.f);
	}
	if (nullptr != m_pPlayer && m_pPlayer->GetName() == L"DeadPlayer")
	{
		m_bIsCaptured = false;
		m_pPlayer = nullptr;
	}
}

void CKey::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CKey::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	if (L"Player" == pObj->GetName())
	{
		m_bIsCaptured = true;
		m_pPlayer = (CPlayer*)pObj;
	}
}

void CKey::OnCollision(CCollider* _pOther)
{
	GetRigidBody()->SetFricCoeff(400.0f);

	if (m_pCurPlate == _pOther->GetObj())
	{
		//중심과의 거리에 비례해서 힘을 다르게 주자
		Vector2D plateCenter = m_pCurPlate->GetPos();
		float plateWidth = m_pCurPlate->GetScale().x / 2.f;
		float dist = abs(plateCenter.x - GetPos().x);
		float ratio = dist / plateWidth;

		GetRigidBody()->SetVelocity(Vector2D((.5f + ratio) * 400.0f * m_iDir, (.5f + ratio) * -250.0f));
		m_pCurPlate = nullptr;
	}
}

void CKey::UpdateAnim()
{
	if (m_iDir == 1)
		GetAnimator()->Play(L"KeyRight", true);
	else
		GetAnimator()->Play(L"KeyLeft", true);
}

void CKey::BeThrown(CObject* _pObj, int _Dir)
{
	m_pCurPlate = _pObj;
	m_iDir = _Dir;
}
