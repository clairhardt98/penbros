#include "pch.h"
#include "CObject.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CCore.h"

CObject::CObject()
	:m_vPos{}
	,m_vScale{}
	,m_pCollider(nullptr)
	,m_pAnimator(nullptr)
	,m_pRigidBody(nullptr)
	,m_bAlive(true)
	,m_pGraphics(nullptr)
	,m_fRotateAmount(0)
{
}

CObject::CObject(const CObject& _origin)
	:m_strName(_origin.m_strName)
	,m_vPos(_origin.m_vPos)
	,m_vScale(_origin.m_vScale)
	,m_pCollider(nullptr)
	,m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	,m_bAlive(true)
	, m_fRotateAmount(0)
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
	if (_origin.m_pRigidBody)
	{
		m_pRigidBody = new CRigidBody(*_origin.m_pRigidBody);
		m_pRigidBody->m_pOwner = this;
	}
	if (_origin.m_pGraphics)
	{
		m_pGraphics = new Gdiplus::Graphics(CCore::GetInst()->GetMemDC());
	}
	
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;

	if (nullptr != m_pAnimator)
		delete m_pAnimator;

	if (nullptr != m_pRigidBody)
		delete m_pRigidBody;
	if (nullptr != m_pGraphics)
		delete m_pGraphics;
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

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}

void CObject::CreateGraphics()
{
	m_pGraphics = new Gdiplus::Graphics(CCore::GetInst()->GetMemDC());
}


void CObject::RotatePos(Vector2D _refVector, float _amount)
{
	
	float angleRadians = _amount * PI / 180.0f;
	m_fRotateAmount += angleRadians;
	float cosTheta = std::cos(angleRadians);
	float sinTheta = std::sin(angleRadians);

	Vector2D vPos = GetPos();
	float translatedX = vPos.x - _refVector.x;
	float translatedY = vPos.y - _refVector.y;

	float rotatedX = translatedX * cosTheta - translatedY * sinTheta;
	float rotatedY = translatedX * sinTheta + translatedY * cosTheta;

	rotatedX += _refVector.x;
	rotatedY += _refVector.y;
	vPos.x = rotatedX;
	vPos.y = rotatedY;

	SetPos(vPos);
	if (abs(m_fRotateAmount) >= PI)
	{
		tEvent eve;
		eve.eEven = EVENT_TYPE::SPIN_END;
		CEventMgr::GetInst()->AddEvent(eve);
		m_fRotateAmount = 0;
	}
}

void CObject::FinalUpdate()
{
	if (m_pRigidBody)
		m_pRigidBody->FinalUpdate();
	if (m_pCollider)
		m_pCollider->FinalUpdate();
	if (m_pAnimator)
		m_pAnimator->FinalUpdate();
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
