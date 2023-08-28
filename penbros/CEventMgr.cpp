#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CSpinPlate.h"
#include "CRigidBody.h"
#include "CImage.h"
#include "CKey.h"
CEventMgr::CEventMgr()
	:m_pPlayer(nullptr)
{

}
CEventMgr::~CEventMgr()
{

}

void CEventMgr::Update()
{
	//이전 프레임의 데드벡터를 체크하고 삭제
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();
	//이벤트 처리
	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		//메시지를 처리하고 메시지를 없애야 함
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Execute(const tEvent& _eve)
{
	//이벤트 타입에 따라서 처리
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
		//lParam : Object Addr
		//wParam : Group Type
	{
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
		//삭제 이벤트가 등록되면 트리거를 올려둠
		//삭제될 오브젝트를 참조하고 있는 다른 오브젝트들이 삭제될 것을 알게됨
		//일단 없어진 오브젝트로 취급하고, 그 다음 프레임에서 실질적인 삭제
		//오브젝트를 dead상태로 변경, 이 오브젝트들을 모아둔다
	{
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		//lParam : next Scene type
		//씬 매니저에게 씬 변경을 요청
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		break;
	case EVENT_TYPE::BOMB_EXPLODED:
		//폭탄이 터지면 플레이어
		m_pPlayer->SetCanSetBomb(true);
		break;
	case EVENT_TYPE::SPIN_START:
	{
		m_pPlayer->SetSpinning(true);
	
		CSpinPlate* pPlate = (CSpinPlate*)_eve.lParam;
		m_pPlayer->SetSpinCenter(pPlate->GetPos());
		m_pPlayer->SetSpinClockwise((int)_eve.wParam);
		m_pPlayer->GetRigidBody()->SetVelocity(Vector2D(0.f, 0.f));
		m_pPlayer->GetRigidBody()->ResetAccel();
		m_pPlayer->GetRigidBody()->EnableGravity(false);
		m_pPlayer->SetName(L"PlayerSpinning");
	}
		break;
	case EVENT_TYPE::SPIN_END:
		m_pPlayer->SetSpinning(false);
		
		//sticked 가 아니라면 중력 복구
		if(!m_pPlayer->IsSticked())
			m_pPlayer->GetRigidBody()->EnableGravity(true);
		m_pPlayer->SetName(L"Player");


		break;
	case EVENT_TYPE::THROW_BOMB:
	{
		if (nullptr != m_pBomb)
			m_pBomb->BeThrown((CObject*)_eve.lParam, (int)_eve.wParam);

		CKey* temp = (CKey*)CSceneMgr::GetInst()->GetCurScene()->GetKey();
		if(nullptr!=temp)
			temp->BeThrown((CObject*)_eve.lParam, (int)_eve.wParam);
	}
		break;
	case EVENT_TYPE::PLAYER_HIT:
		m_pPlayer->Hit();
		break;
	case EVENT_TYPE::EXPLOSION_HIT:
	{
		CObject* pObj = (CObject*)_eve.lParam;
		pObj->Hit();
		break;
	}
	case EVENT_TYPE::PLAYER_REVIVE:
	{
		CSceneMgr::GetInst()->GetCurScene()->RevivePlayer();
		break;
	}
	case EVENT_TYPE::STAGE_CLEAR:
		CSceneMgr::GetInst()->GetCurScene()->SetCleared(true);
		DeleteObject(CSceneMgr::GetInst()->GetCurScene()->GetKey());
		
		break;
	}
}


