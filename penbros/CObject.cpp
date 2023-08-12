#include "pch.h"
#include "CObject.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CAnimator.h"

CObject::CObject()
	:m_vPos{}
	,m_vScale{}
	,m_pCollider(nullptr)
	,m_pAnimator(nullptr)
	,m_bAlive(true)
{
}

CObject::CObject(const CObject& _origin)
	:m_strName(_origin.m_strName)
	,m_vPos(_origin.m_vPos)
	,m_vScale(_origin.m_vScale)
	,m_pCollider(nullptr)
	,m_pAnimator(nullptr)
	,m_bAlive(true)
{
	//CCollider의 복사생성자 호출해서 새로운 콜라이더 생성
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
	
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;

	if (nullptr != m_pAnimator)
		delete m_pAnimator;
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

void CObject::FinalUpdate()
{
	if (m_pCollider)
		m_pCollider->FinalUpdate();
}

void CObject::Render(HDC _dc)
{
	Rectangle(_dc,(int)(m_vPos.x - m_vScale.x / 2.0f), (int)(m_vPos.y - m_vScale.y / 2.0f),
				  (int)(m_vPos.x + m_vScale.x / 2.0f), (int)(m_vPos.y + m_vScale.y / 2.0f));
	ComponentRender(_dc);
}

void CObject::ComponentRender(HDC _dc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->Render(_dc);
	}
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Render(_dc);
	}
}
