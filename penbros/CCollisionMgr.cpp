#include "pch.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	:m_arrCheck{}
{

}
CCollisionMgr::~CCollisionMgr()
{


}
void CCollisionMgr::Init()
	
{
}
void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ)�� ���
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		//�̹� ä���� �ִٸ�
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	//1�� col��ŭ �������� shift�ؼ� and���� ���ش�
	m_arrCheck[iRow] |= (1 << iCol);
}
void CCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		m_arrCheck[iRow];
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				//�浹 ����
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}
void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	//������ �� ���� ������ �޾ƾ� ��
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	map<ULONGLONG, bool>::iterator iter;
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->GetCollider())
		{
			//�ش� ������Ʈ�� �浹ü�� ���� ���� ����
			continue;
		}
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			//�� �ڽŰ��� �浹�� ����
			//�ش� ������Ʈ�� �浹ü�� ���� ���� ����
			if (nullptr == vecRight[j]->GetCollider() ||
				vecLeft[i] == vecRight[j])
			{
				continue;

			}
			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();
			//�� �浹ü ���� ID ����
			COLLIDER_ID ID;
			//8����Ʈ�� ��ġ�� �ʴ� �� ������ ä���
			ID.left_id = pLeftCol->GetID();
			ID.right_id = pRightCol->GetID();
			//ID.ID -> map�� Ű ������ ���
			iter = m_mapColInfo.find(ID.ID);

			if (m_mapColInfo.end() == iter)
			{
				//��ϵ��� ���� �浹 ������ ���
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}
			if (IsCollision(pLeftCol, pRightCol))
			{
				//���� �浹��
				if (iter->second)
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						//����ó�� ������ ������Ʈ���� �浹���̶�� �浹 �����
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					//���� �����ӿ��� �浹��
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					//������ �浹���� �ʾҴٰ� ���� �浹�� ���
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						//����ó�� ������ ������Ʈ���� �浹���̶�� �浹 �����
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				if (iter->second)
				{
					//�浹���� ���
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}

}
bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vector2D vLeftPos = _pLeftCol->GetFinalPos();
	Vector2D vLeftScale = _pLeftCol->GetScale();
	Vector2D vRightPos = _pRightCol->GetFinalPos();
	Vector2D vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.0f 
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.0f)
		return true;
	else
		return false;
}





