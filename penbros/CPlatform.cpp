#include "pch.h"
#include "CPlatform.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"



CPlatform::CPlatform()
{
	CreateCollider();
	CreateAnimator();

	CAnimator* pAnim = GetAnimator();

	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlatformTexture", L"Image\\Platform.bmp");
	pAnim->CreateAnimation(true, L"PlatformIdle", pTex, 1, 1, 0, 0, Vector2D(240.f, 32.f), .1f, 1);
	pAnim->Play(L"PlatformIdle", true);

}

CPlatform::~CPlatform()
{
}

void CPlatform::Start()
{
	GetCollider()->SetScale(Vector2D(GetScale()));
}

void CPlatform::Update()
{
}


void CPlatform::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Bomb" || pOtherObj->GetName() == L"DeadPlayer")
	{
		Vector2D vObjPos = _pOther->GetFinalPos();
		Vector2D vObjScale = _pOther->GetScale();
		int temp;
		if (vObjPos.y > GetPos().y)
			temp = 1;
		else
			temp = -1;
		pOtherObj->GetRigidBody()->SetGrounded(true);

		Vector2D vPos = GetPos();
		Vector2D vScale = GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fDist = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetPos();
		vObjPos.y += temp * fDist;

		pOtherObj->SetPos(vObjPos);
	}
}

void CPlatform::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Bomb" || pOtherObj->GetName() == L"DeadPlayer")
	{
		Vector2D vObjPos = _pOther->GetFinalPos();
		Vector2D vObjScale = _pOther->GetScale();
		if (vObjPos.y > GetPos().y)return;
		pOtherObj->GetRigidBody()->SetGrounded(true);


		Vector2D vPos = GetPos();
		Vector2D vScale = GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fDist = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= fDist;
		pOtherObj->SetPos(vObjPos);
	}
}

void CPlatform::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Bomb" || pOtherObj->GetName() == L"DeadPlayer")
	{
		pOtherObj->GetRigidBody()->SetGrounded(false);
	}
}

void CPlatform::Render(HDC _dc)
{
	//CObject::Render(_dc);
	ComponentRender(_dc);
}