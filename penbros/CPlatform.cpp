#include "pch.h"
#include "CPlatform.h"
#include "CCollider.h"
#include "CRigidBody.h"



CPlatform::CPlatform()
{
	CreateCollider();
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
	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Bomb")
	{
		pOtherObj->GetRigidBody()->SetGrounded(true);
		Vector2D vObjPos = _pOther->GetFinalPos();
		Vector2D vObjScale = _pOther->GetScale();

		Vector2D vPos = GetPos();
		Vector2D vScale = GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fDist = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= fDist;

		pOtherObj->SetPos(vObjPos);
	}
}

void CPlatform::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Bomb")
	{
		//pOtherObj->GetRigidBody()->SetGrounded(true);
		Vector2D vObjPos = _pOther->GetFinalPos();
		Vector2D vObjScale = _pOther->GetScale();

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
	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Bomb")
	{
		pOtherObj->GetRigidBody()->SetGrounded(false);
	}
}

void CPlatform::Render(HDC _dc)
{
	//CObject::Render(_dc);
	ComponentRender(_dc);
}