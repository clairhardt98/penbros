#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CScene.h"
#include "CSceneMgr.h"
CEventMgr::CEventMgr()
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
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
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
	}

}
