#include "pch.h"
#include "CExplosion.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CEventMgr.h"

CExplosion::CExplosion()
{
	//Collider�� Animator ����
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2D(0.0f, 0.0f));
	GetCollider()->SetScale(Vector2D(40.0f, 40.0f));

	CreateAnimator();
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"ExplosionTexture", L"Image\\Explosion.bmp");

	CAnimator* pAnim = GetAnimator();
	pAnim->CreateAnimation(true, L"EXPLOSION", pTex, 1, 6, 0, 0, Vector2D(64.f, 64.f), 0.05f, 6);
	CAnimation* pExplosionAnim = pAnim->FindAnimation(L"EXPLOSION");

	/*for (int i = 0; i < pExplosionAnim->GetMaxFrame(); i++)
		pExplosionAnim->GetFrame(i).vOffset = Vector2D(0.f, -15.f);*/

	pAnim->Play(L"EXPLOSION", false);
}

CExplosion::~CExplosion()
{
}


void CExplosion::Update()
{
	if (GetAnimator()->GetCurAnimation()->IsFinish())
		DeleteObject(this);
}

void CExplosion::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CExplosion::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	//�̺�Ʈ ����, lParam�� �浹�� ��ü�� ������, wParam�� null
	tEvent eve = {};
	eve.eEven = EVENT_TYPE::EXPLOSION_HIT;
	eve.lParam = (DWORD_PTR)pObj;
	eve.wParam = NULL;
	CEventMgr::GetInst()->AddEvent(eve);
}

