#include "pch.h"
#include "CBomb.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CEventMgr.h"
#include "CExplosion.h"

CBomb::CBomb()
	:m_fExplosionTime(0)
	,m_eBMod(BOMB_MODE::NORMAL)
	,m_iDir(1)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2D(0.0f, 0.0f));
	GetCollider()->SetScale(Vector2D(35.0f, 35.0f));

	CreateRigidBody();
	GetRigidBody()->EnableGravity(true);
	//normal ��ź�� ���� �ִϸ��̼� �Ҵ� �� ����, �÷���
}

CBomb::CBomb(BOMB_MODE _bm)
	:m_fExplosionTime(0)
	, m_eBMod(_bm)
	, m_iDir(1)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2D(0.0f, 0.0f));
	GetCollider()->SetScale(Vector2D(35.0f, 35.0f));

	CreateRigidBody();
	GetRigidBody()->EnableGravity(true);
	//bm�� ���� �ִϸ��̼� �Ҵ� �� ����, �÷���
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
	Vector2D vPos = GetPos();
	Vector2D vScale = GetScale();
	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.0f), (int)(vPos.y - vScale.y / 2.0f),
		(int)(vPos.x + vScale.x / 2.0f), (int)(vPos.y + vScale.y / 2.0f));
	ComponentRender(_dc);
}

void CBomb::Explode()
{
	BombExploded();
	Vector2D vPos = GetPos();
	//Explosion ��ü ����
	
	switch (m_eBMod)
	{
	case BOMB_MODE::NORMAL:
	{
		//explosion 3�� ����
		for (int i = -1; i < 2; ++i)
		{
			CreateExplosion(Vector2D(vPos.x + i * m_fExplosionInterval, vPos.y));
		}
	}
		break;
	case BOMB_MODE::BLUE:
	{
		//�Ʒ� �� ��, ���� �� �� ����
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
		//5 �� ����
		for (int i = -2; i < 3; ++i)
		{
			CreateExplosion(Vector2D(vPos.x + i * m_fExplosionInterval, vPos.y));
		}
	}
		break;
	case BOMB_MODE::GREEN:
	{
		//5�� �����ϵ�, �������� �ϳ�, ���������� �� ��
		for (int i = -1; i < 4; ++i)
		{
			CreateExplosion(Vector2D(vPos.x + i * m_fExplosionInterval, vPos.y));
		}
	}
		break;
	}
	
	DeleteObject(this);
}

void CBomb::CreateExplosion(Vector2D _vPos)
{
	CExplosion* pExp = new CExplosion;
	pExp->SetPos(_vPos);
	pExp->SetScale(Vector2D(70.0f, 70.0f));
	CreateObject(pExp, GROUP_TYPE::EXPLOSION);
}


