#include "pch.h"
#include "CBomb.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CEventMgr.h"
#include "CExplosion.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CEventMgr.h"

CBomb::CBomb()
	:m_fExplosionTime(0)
	, m_eBMod(BOMB_MODE::NORMAL)
	, m_iDir(1)
	, m_pCurPlate(nullptr)
{
	CreateAnimator();
	CTexture* pTexRight = CResMgr::GetInst()->LoadTexture(L"BombTextureRight", L"Image\\Bomb.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTexture(L"BomTextureLeft", L"Image\\Bomb_left.bmp");
	CAnimator* pAnim = GetAnimator();

	pAnim->CreateAnimation(true, L"BombRight", pTexRight, 1, 7, 0, 0, Vector2D(40.f, 40.f), 0.45f, 7);
	pAnim->CreateAnimation(false, L"BombLeft", pTexLeft, 1, 7, 0, 0, Vector2D(40.f, 40.f), 0.45f, 7);

	pAnim->Play(L"BombRight",false);

	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2D(0.0f, 0.0f));
	GetCollider()->SetScale(Vector2D(35.0f, 35.0f));

	CreateRigidBody();
	GetRigidBody()->EnableGravity(true);
	
	CEventMgr::GetInst()->SetBomb(this);
	//normal 폭탄에 대한 애니메이션 할당 및 생성, 플레이
}

CBomb::CBomb(BOMB_MODE _bm, int _dir)
	:m_fExplosionTime(0)
	, m_eBMod(_bm)
	, m_iDir(_dir)
	, m_pCurPlate(nullptr)
{
	CreateAnimator();
	CTexture* pTexRight = CResMgr::GetInst()->LoadTexture(L"BombTextureRight", L"Image\\Bomb.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTexture(L"BomTextureLeft", L"Image\\Bomb_left.bmp");
	CAnimator* pAnim = GetAnimator();


	if (m_iDir == 1)
	{
		pAnim->CreateAnimation(true, L"BombRight", pTexRight, 1, 7, 0, 0, Vector2D(40.f, 40.f), 0.4f, 7);
		pAnim->Play(L"BombRight", false);
	}
	else
	{
		pAnim->CreateAnimation(false, L"BombLeft", pTexLeft, 1, 7, 0, 0, Vector2D(40.f, 40.f), 0.4f, 7);
		pAnim->Play(L"BombLeft", false);
	}

	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2D(0.0f, 0.0f));
	GetCollider()->SetScale(Vector2D(35.0f, 35.0f));

	CreateRigidBody();
	GetRigidBody()->EnableGravity(true);
	//bm에 따른 애니메이션 할당 및 생성, 플레이
	CEventMgr::GetInst()->SetBomb(this);

}



CBomb::~CBomb()
{
}

void CBomb::Update()
{
	m_fExplosionTime += fDT;
	if (m_fExplosionTime >= 3.0f)
	{
		Explode();
	}
}

void CBomb::Render(HDC _dc)
{
	/*Vector2D vPos = GetPos();
	Vector2D vScale = GetScale();
	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.0f), (int)(vPos.y - vScale.y / 2.0f),
		(int)(vPos.x + vScale.x / 2.0f), (int)(vPos.y + vScale.y / 2.0f));*/
	ComponentRender(_dc);
}

void CBomb::OnCollisionEnter(CCollider* _pOther)
{
	GetRigidBody()->SetFricCoeff(400.0f);
}

void CBomb::OnCollision(CCollider* _pOther)
{
	GetRigidBody()->SetFricCoeff(400.0f);

	if (m_pCurPlate == _pOther->GetObj())
	{
		//중심과의 거리에 비례해서 힘을 다르게 주자
		Vector2D plateCenter = m_pCurPlate->GetPos();
		float plateWidth = m_pCurPlate->GetScale().x /2.f;
		float dist = abs(plateCenter.x - GetPos().x);
		float ratio = dist / plateWidth;
		
		GetRigidBody()->AddVelocity(Vector2D((.5f + ratio)* 300.0f * m_iDir, (.5f + ratio) *  -200.0f));
		m_pCurPlate = nullptr;
	}
}

void CBomb::OnCollisionExit(CCollider* _pOther)
{
	GetRigidBody()->SetFricCoeff(0.f);

}



void CBomb::Explode()
{
	BombExploded();
	Vector2D vPos = GetPos();
	//Explosion 객체 생성
	
	switch (m_eBMod)
	{
	case BOMB_MODE::NORMAL:
	{
		//explosion 3개 생성
		for (int i = -1; i < 2; ++i)
		{
			CreateExplosion(Vector2D(vPos.x + i * m_fExplosionInterval, vPos.y));
		}
	}
		break;
	case BOMB_MODE::BLUE:
	{
		//아래 세 개, 위로 두 개 생성
		for (int i = -1; i < 2; ++i)
		{
			CreateExplosion(Vector2D(vPos.x + i * m_fExplosionInterval, vPos.y));
		}
		CreateExplosion(Vector2D(vPos.x - m_fExplosionInterval / 2, vPos.y - m_fExplosionInterval));
		CreateExplosion(Vector2D(vPos.x + m_fExplosionInterval / 2, vPos.y - m_fExplosionInterval));
	}
		break;
	case BOMB_MODE::RED:
	{
		//5 개 생성
		for (int i = -2; i < 3; ++i)
		{
			CreateExplosion(Vector2D(vPos.x + i * m_fExplosionInterval, vPos.y));
		}
	}
		break;
	case BOMB_MODE::GREEN:
	{
		//5개 생성하되, 왼쪽으로 하나, 오른쪽으로 네 개
		for (int i = -2 + m_iDir; i < 3 + m_iDir; ++i)
		{
			CreateExplosion(Vector2D(vPos.x + i * m_fExplosionInterval, vPos.y));
		}
	}
		break;
	}
	CEventMgr::GetInst()->SetBomb(nullptr);

	DeleteObject(this);
}

void CBomb::BeThrown(CObject* _pObj, int _Dir)
{
	m_pCurPlate = _pObj;
	m_iDir = _Dir;
}

void CBomb::CreateExplosion(Vector2D _vPos)
{
	CExplosion* pExp = new CExplosion;
	pExp->SetPos(_vPos);
	pExp->SetScale(Vector2D(70.0f, 70.0f));
	CreateObject(pExp, GROUP_TYPE::EXPLOSION);
}


