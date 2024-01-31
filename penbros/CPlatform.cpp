#include "pch.h"
#include "CPlatform.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CObject.h"



CPlatform::CPlatform()
{
	CreateCollider();
	CreateAnimator();
}

CPlatform::~CPlatform()
{
}

void CPlatform::Start()
{
	GetCollider()->SetScale(Vector2D(GetScale()));
	CAnimator* pAnim = GetAnimator();
	CTexture* pTex = nullptr;
	wstring objName = GetName();
	wstring animationName;
	//�÷����� �̸��� ���� �ٸ� �ִϸ��̼� ����
	if (L"BottomWall" == objName)
	{
		pTex = CResMgr::GetInst()->LoadTexture(L"TopWallTexture", L"Image\\TopWall.bmp");
		animationName = L"TopWallIdle";
	}
	if (L"Platform" == objName)
	{
		pTex = CResMgr::GetInst()->LoadTexture(L"PlatformTexture", L"Image\\Platform.bmp");
		animationName = L"PlatformIdle";
	}
	if (L"Wall" == objName)
	{
		pTex = CResMgr::GetInst()->LoadTexture(L"WallTexture", L"Image\\SideWall.bmp");
		animationName = L"WallIdle";
	}

	if (pTex != nullptr) 
	{
		pAnim->CreateAnimation(true, animationName, pTex, 1, 1, 0, 0, GetScale(), .1f, 1);
		pAnim->Play(animationName, true);
	}
}

void CPlatform::Update()
{
}

void CPlatform::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player" || pOtherObj->GetName() == L"Bomb" || pOtherObj->GetName() == L"DeadPlayer" || pOtherObj->GetName() == L"Key" || pOtherObj->GetName() == L"Monster")
	{
		Vector2D vObjPos = _pOther->GetFinalPos();
		Vector2D vObjScale = _pOther->GetScale();
		
		Vector2D vPos = GetPos();
		Vector2D vScale = GetScale();

		//���� �����Ӱ��� �浹�ϴ� ���, �¿� �����Ӱ��� �浹�ϴ� ��츦 ��������

		if (vObjPos.x >= vPos.x - vScale.x / 2.f && vObjPos.x <= vPos.x + vScale.x / 2.f)
		{
			//�����ؼ� �Ʒ����� ���� �ö� �� �÷����� �ε����� ���� ��������
			if (vObjPos.y > GetPos().y)return;

			pOtherObj->GetRigidBody()->SetGrounded(true);

			float fLen = abs(vObjPos.y - vPos.y);
			float fDist = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = pOtherObj->GetPos();
			vObjPos.y -= fDist;
			pOtherObj->SetPos(vObjPos);
		}
		else
		{
			if (vObjPos.y > vPos.y + vScale.y / 2.f || vObjPos.y < vPos.y - vScale.y / 2.f)return; 
			int temp = vObjPos.x >= vPos.x ? -1 : 1;
			//���ϰ� �ƴ� ��� �¿�
			float fLen = abs(vObjPos.x - vPos.x);
			float fDist = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;

			vObjPos = pOtherObj->GetPos();
			vObjPos.x -= temp * fDist;
			pOtherObj->SetPos(vObjPos);
		}
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