#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"


//collider의 id
UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	:m_pOwner(nullptr)
	,m_iID(g_iNextID++)
{
}

CCollider::CCollider(const CCollider& _origin)
	:m_pOwner(nullptr)
	,m_vOffsetPos(_origin.m_vOffsetPos)		
	,m_vScale(_origin.m_vScale)
	,m_iID(g_iNextID++)
{
}

CCollider::~CCollider()
{
}

void CCollider::FinalUpdate()
{
	//오브젝트의 위치를 따라간다 ->render하기 전에
	Vector2D vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;//오브젝트의 위치 + 오프셋
	assert(0 <= m_iCol);
}

void CCollider::Render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol)ePen = PEN_TYPE::RED;

	//임시객체 생성했기 때문에 함수 종료시 객체 소멸, 소멸자에서 다시 원래 펜과 브러시로 돌려놓음
	SelectGDI p(_dc, ePen);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, (int)(m_vFinalPos.x - m_vScale.x / 2.0f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.0f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.0f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.0f));
	
}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	m_pOwner->OnCollisionEnter(_pOther);
	++m_iCol;
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	m_pOwner->OnCollisionExit(_pOther);
	--m_iCol;
}


