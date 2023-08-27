#include "pch.h"
#include "CRigidBody.h"
#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	:m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoeff(200.f)
	, m_vMaxVelocity(Vector2D(300.f, 500.f))
	, m_bIsGravityOn(false)
	, m_bIsGrounded(false)
	, m_vGravity(Vector2D(0.f, 800.f))
{
}

CRigidBody::~CRigidBody()
{
}
void CRigidBody::FinalUpdate()
{

	float fForce = m_vForce.mag();
	if (0.f != fForce)
	{
		m_vAccel = m_vForce / m_fMass;
	}
	//중력이 켜져있고, 땅 위에 있는게 아니라면
	
	//마찰력 적용
	//이번 프레임에 적용될 마찰력에 의한 반대방향으로의 가속도
	if (m_vVelocity.mag() != 0)
	{
		//현재 속도가 0이 아닐 때만 마찰력 적용
		Vector2D vTemp = m_vVelocity * -1;
		vTemp.normalize();
		Vector2D vFriction = vTemp * m_fFricCoeff * fDT;
		if (m_vVelocity.mag() <= vFriction.mag())
		{
			//마찰력이 더 큰 경우
			m_vVelocity = Vector2D(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	if (m_bIsGravityOn)
		UpdateGravity();

	m_vVelocity += m_vAccel * fDT;
	//최대 속도 제한
	if (m_vVelocity.x != 0 && m_vMaxVelocity.x < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}
	if (m_vVelocity.y != 0 && m_vMaxVelocity.y < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}
	//이동

	Move();
	//축적된 힘을 주고 다시 0으로 초기화

	m_vForce = Vector2D(0.f, 0.f);
	ResetAccel();
}

void CRigidBody::UpdateGravity()
{
	m_vAccel += m_vGravity;
}

void CRigidBody::Move()
{
	float fSpeed = m_vVelocity.mag();
	if (0.f != fSpeed)
	{
		Vector2D vPos = m_pOwner->GetPos();
		vPos += m_vVelocity * fDT;
		m_pOwner->SetPos(vPos);
	}
}
