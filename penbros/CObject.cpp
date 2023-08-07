#include "pch.h"
#include "CObject.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"

CObject::CObject()
	:m_vPos{}
	, m_vScale{}
	,m_pCollider(nullptr)
{
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
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
}
