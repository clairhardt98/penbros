#include "pch.h"
#include "CKey.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidBody.h"
CKey::CKey()
	:m_pPlayer(nullptr)
	,m_bIsCaptured(false)
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
	if (m_bIsCaptured && nullptr!=m_pPlayer)
	{
		Vector2D vPlayerPos = m_pPlayer->GetPos();
		SetPos(vPlayerPos);
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
		m_pPlayer = pObj;
		//플레이어의 holdingKey를 바꿔줌 -> 이벤트 보내야겠지?

	}
}
