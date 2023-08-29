#include "pch.h"
#include "CCrabProjectile.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CTexture.h"
#include "CResMgr.h"

CCrabProjectile::CCrabProjectile()
	:m_iDir(1)
{
	CreateCollider();
	GetCollider()->SetScale(Vector2D(10.f, 10.f));
	CreateRigidBody();
	GetRigidBody()->EnableGravity(false);
	GetRigidBody()->SetFricCoeff(0.f);

	m_pTexRight = CResMgr::GetInst()->LoadTexture(L"CrapProjectileRight", L"Image\\CrabProjectile.bmp");
	m_pTexLeft = CResMgr::GetInst()->LoadTexture(L"CrapProjectileLeft", L"Image\\CrabProjectile_Left.bmp");

}

CCrabProjectile::~CCrabProjectile()
{

}
void CCrabProjectile::Update()
{
	//GetRigidBody()->AddForce(Vector2D(m_iDir * 100.0f, 0.f));
	//앞으로 쭉 나가는 로직
	Vector2D vPos = GetPos();
	if (vPos.x > 800.0f || vPos.x < 0)
		DeleteObject(this);
}

void CCrabProjectile::Render(HDC _dc)
{
	/*Vector2D vPos = GetPos();
	Vector2D vScale = GetScale();
	Ellipse(_dc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2.f, vPos.x + vScale.x / 2, vPos.y + vScale.y / 2.f);*/
	Vector2D vPos = GetPos();
	Vector2D vScale = GetScale();
	if (m_iDir == 1)
	{
		TransparentBlt(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f), (int)vScale.x, (int)vScale.y, m_pTexRight->GetDC(), 0, 0, (int)vScale.x, (int)vScale.y, RGB(255, 0, 255));
	}
	else
	{
		TransparentBlt(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f), (int)vScale.x, (int)vScale.y, m_pTexLeft->GetDC(), 0, 0, (int)vScale.x, (int)vScale.y, RGB(255, 0, 255));

	}
	ComponentRender(_dc);
}

void CCrabProjectile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	if(L"Player" == pObj->GetName())
	{
		pObj->Hit();
		DeleteObject(this);
	}
}


