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
	//�߷��� �����ְ�, �� ���� �ִ°� �ƴ϶��
	
	//������ ����
	//�̹� �����ӿ� ����� �����¿� ���� �ݴ���������� ���ӵ�
	if (m_vVelocity.mag() != 0)
	{
		//���� �ӵ��� 0�� �ƴ� ���� ������ ����
		Vector2D vTemp = m_vVelocity * -1;
		vTemp.normalize();
		Vector2D vFriction = vTemp * m_fFricCoeff * fDT;
		if (m_vVelocity.mag() <= vFriction.mag())
		{
			//�������� �� ū ���
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
	//�ִ� �ӵ� ����
	if (m_vVelocity.x != 0 && m_vMaxVelocity.x < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}
	if (m_vVelocity.y != 0 && m_vMaxVelocity.y < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}
	//�̵�

	Move();
	//������ ���� �ְ� �ٽ� 0���� �ʱ�ȭ

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
