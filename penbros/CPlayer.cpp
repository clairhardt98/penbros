#include "pch.h"
#include "CPlayer.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CMissile.h"
#include "CScene.h"
#include "CAnimator.h"
#include "CAnimation.h"


CPlayer::CPlayer()
{
	//리소스 매니저를 통한 리소스 로딩
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2D(0.0f, 0.0f));
	GetCollider()->SetScale(Vector2D(25.0f, 25.0f));

	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"Image\\bomberman.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK",pTex, Vector2D(0.0f, 0.0f), Vector2D(28.5f, 50.0f), Vector2D(28.5f, 0.0f), 0.1f, 5);

	GetAnimator()->Play(L"WALK",true);
	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK");
	//애니메이터의 오프셋 세팅 -> 필요한가?
	for(int i = 0; i<pAnim->GetMaxFrame();i++)
		pAnim->GetFrame(i).vOffset = Vector2D(0.f, -20.f);
}

CPlayer::~CPlayer()
{

}
void CPlayer::Update()
{
	Vector2D vPos = GetPos();
	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.0f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.0f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.0f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.0f * fDT;
	}
	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
	GetAnimator()->Update();
}

void CPlayer::Render(HDC _dc)
{
	//본인이 보유하고 있는 애니메이션 정보
	ComponentRender(_dc);
}

void CPlayer::CreateMissile()
{
	Vector2D vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.0f;

	CMissile* pMissile = new CMissile;

	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vector2D(25.0f, 25.0f));
	pMissile->SetDir(Vector2D(0.0f, -1.0f));

	/*CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile,GROUP_TYPE::PROJ_PLAYER);*/

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

