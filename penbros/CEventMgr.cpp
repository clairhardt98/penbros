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
	//���� �������� ���庤�͸� üũ�ϰ� ����
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();
	//�̺�Ʈ ó��
	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		//�޽����� ó���ϰ� �޽����� ���־� ��
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	//�̺�Ʈ Ÿ�Կ� ���� ó��
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
		//���� �̺�Ʈ�� ��ϵǸ� Ʈ���Ÿ� �÷���
		//������ ������Ʈ�� �����ϰ� �ִ� �ٸ� ������Ʈ���� ������ ���� �˰Ե�
		//�ϴ� ������ ������Ʈ�� ����ϰ�, �� ���� �����ӿ��� �������� ����
		//������Ʈ�� dead���·� ����, �� ������Ʈ���� ��Ƶд�
	{
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}

		break;
	case EVENT_TYPE::SCENE_CHANGE:
		//lParam : next Scene type
		//�� �Ŵ������� �� ������ ��û
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		break;
	}

}
