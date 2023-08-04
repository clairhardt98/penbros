#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"

CMonster::CMonster()
	:m_vCenterPos(Vector2D(0.0f, 0.0f))
	,m_fSpeed(100.0f)
	,m_fMaxDistance(50.0f)
	,m_iDir(1)
{
}

CMonster::~CMonster()
{
}

void CMonster::Update()
{
	Vector2D vCurPos = GetPos();

	//���� �������� �ð��� m_fSpeed��ŭ �̵�

	vCurPos.x += fDT * m_fSpeed * m_iDir;

	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance; // �ʰ���

	if (0.0f < fDist)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;//dt���� �ʰ��� �� ��ŭ �ٽ� �ݴ�������� �������ش�
	}
	SetPos(vCurPos);
	m_vCenterPos;
}
