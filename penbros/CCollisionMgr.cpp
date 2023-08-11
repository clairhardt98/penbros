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
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트)로 사용
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		//이미 채워져 있다면
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	//1을 col만큼 왼쪽으로 shift해서 and연산 해준다
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
				//충돌 진행
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}
void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	//참조로 준 것을 참조로 받아야 함
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	map<ULONGLONG, bool>::iterator iter;
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->GetCollider())
		{
			//해당 오브젝트가 충돌체가 없을 수도 있음
			continue;
		}
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			//나 자신과의 충돌은 예외
			//해당 오브젝트가 충돌체가 없을 수도 있음
			if (nullptr == vecRight[j]->GetCollider() ||
				vecLeft[i] == vecRight[j])
			{
				continue;

			}
			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();
			//두 충돌체 조합 ID 생성
			COLLIDER_ID ID;
			//8바이트를 겹치지 않는 두 값으로 채운다
			ID.left_id = pLeftCol->GetID();
			ID.right_id = pRightCol->GetID();
			//ID.ID -> map의 키 값으로 사용
			iter = m_mapColInfo.find(ID.ID);

			if (m_mapColInfo.end() == iter)
			{
				//등록되지 않은 충돌 정보인 경우
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}
			if (IsCollision(pLeftCol, pRightCol))
			{
				//현재 충돌중
				if (iter->second)
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						//삭제처리 예정인 오브젝트와의 충돌중이라면 충돌 벗어나게
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					//이전 프레임에도 충돌중
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					//이전엔 충돌하지 않았다가 이제 충돌한 경우
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						//삭제처리 예정인 오브젝트와의 충돌중이라면 충돌 벗어나게
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
					//충돌에서 벗어남
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





