#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CCollider.h"

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}

CMissile::CMissile()
	:m_fTheta(PI/4.f)
	,m_vDir(0.0f, -1.0f)
{
	m_vDir.normalize();
	CreateCollider();
	GetCollider()->SetScale(Vector2D(15.f, 15.f));
}
CMissile::~CMissile()
{

}
void CMissile::Update()
{
	Vector2D vPos = GetPos();
	vPos.x += 600.0f * fDT * (float)m_vDir.x;
	vPos.y += 600.0f * fDT * (float)m_vDir.y;

	SetPos(vPos);
}

void CMissile::Render(HDC _dc)
{
	Vector2D vPos = GetPos();
	Vector2D vScale = GetScale();
	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.0f), (int)(vPos.y - vScale.y / 2.0f),
				 (int)(vPos.x + vScale.x / 2.0f), (int)(vPos.y + vScale.y / 2.0f));
	ComponentRender(_dc);
}
